// ======================================================================
// Copyright (C) 2018 Alberto Fuentes Rodríguez <fuentessec@gmail.com>
// This file is part of RamDPA <https://github.com/fuentessec/RamDPA>.
//
// RamDPA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RamDPA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RamDPA.  If not, see <http://www.gnu.org/licenses/>.
// ======================================================================


#include "trace_set.h"

#ifndef CTRACE
#include "trace.h"
#endif 

#ifndef CTIMESLICE
#include "ctimeslice.h"
#endif 

#include "keyhypothesis_allvalues_8set.h"
#include "keyhypothesis_allvalues_16set.h"
#include "intermediate.h"
#include "intermediate_matrix.h"
#include "input_data_set.h"
#include "aes_sub_bytes_output.h"
#include "consumption_matrix.h"
#include "lbs_power_model.h"
#include "hw_power_model.h"
#include "binary_array_matrix.h"
#include "correlation_coefficient.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <list>
#include <string>
#include <valarray>
#include <sys/time.h>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>

#define NUM_TRACES 1000
#define TRACE_SIZE 9996
#define DATA_SIZE 16
#define KEY_SIZE 16

typedef unsigned long long timestamp_t;
using namespace std;

void process_mem_usage(double& vm_usage, double& resident_set) {
    vm_usage = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}

int main(int argc, char *argv[]) {
    timestamp_t begin;
    double diff;

    /// read arguments
    if (argc != 6) {
        printf("Usage: ramdpa-master NumThreds TraceElementPrecision floatPrecision traceFile\n");
        printf("Numthreads = number of threads for parallel calculations\n");
        printf("TraceElementPrecision = 1->8-bits, 2->16-bits, 3->32-bits\n");
        printf("floatPrecision = 1->float(32-bits), 2->double(64bits)\n");
        printf("traceFile = file with traces in integer text format\n");
        printf ("dataFile = file with input plaintexts in integer text format\n\n");
        printf("NOTE: program does not do input validation (put correct values)\n");
        return -1;
    }

    /// set values given as arguments
    setenv("NTHREADS", argv[1], 1);
    int tracePrecision = atoi(argv[2]);
    int floatPrecision = atoi(argv[3]);

    // print configuration
    printf("---- Configuration ----");
    printf("Threads = %s\n", argv[1]);
    switch (tracePrecision) {
        case 1:
            printf("TracePrecision = 8-bits\n");
            break;
        case 2:
            printf("TracePrecision = 16-bits\n");
            break;
        default:
            printf("TracePrecision = 32-bits\n");
    }
    switch (floatPrecision) {
        case 1:
            printf("FloatPrecision = float\n");
            break;
        default:
            printf("FloatPrecision = double\n");
    }


    TraceSet traceSet = TraceSet();
    Trace *aux;

    // open traces file
    printf ("trace file = %s" ,argv[4]);
    ifstream tracesFile(argv[4]);

    // read traces from file and create traceSet
    printf("read traces from file\n");
    begin = get_timestamp();
    for (int i = 0; i < NUM_TRACES; i++) {
        Trace *aux;
        switch (tracePrecision) {
            case 1:
                aux = new Trace8(1000, 1.0 / 1024, -83.0 / 1024, TRACE_SIZE);
                break;
            case 2:
                aux = new Trace16(1000, 1.0 / 1024, -83.0 / 1024, TRACE_SIZE);
                break;
            default:
                aux = new Trace32(1000, 1.0 / 1024, -83.0 / 1024, TRACE_SIZE);
        }

        for (int j = 0; j < TRACE_SIZE; j++) {
            uint16_t value;
            tracesFile >> value;
            aux->setValue(value, j);
        }
        traceSet.addTrace(aux);
    }
    diff = double(get_timestamp() - begin) / 1000000.;
    printf("Time -> %f\n", diff);

    /// PRINT TRACE INFO.
    //    ts1.getNTrace(0)->toPng("traceCHES2016.png");
    //    ts1.toPng("tracesCHES16.png");

    /// CHECK STATISTICS
    //    StatTrace *mean = ts1.meanTraces();
    //    StatTrace *variance = ts1.varianceTraces (mean);
    //    mean->toPng("tracesCHES16mean.png");
    //    variance->toPng("tracesCHES16var.png");

    // change traceset to statistical mode
    printf("change traceset to statistical mode\n");
    begin = get_timestamp();
    traceSet.statMode();
    diff = double(get_timestamp() - begin) / 1000000.;
    printf("Time -> %f\n", diff);

    // create data set
    InputDataSet dataSet = InputDataSet(DATA_SIZE);

    // read data file
    uint8_t auxData [16]; // aux array to hold data for InputData creation.
    printf ("plaintext file = %s" ,argv[5]);
    ifstream dataFile(argv[5]);
    for (int i = 0; i < NUM_TRACES; i++) {

        // reading data form file (size 16 bytes).
        for (int j = 0; j < DATA_SIZE; j++) {
            int aux;
            dataFile >> aux;
            auxData [j] = aux;
        }

        //inserting data into dataSet
        InputData input = InputData(DATA_SIZE, auxData, true);
        dataSet.insertData(input);
    }

    // variables for time spent in each DPA step to obtain complete key
    double timeIntermediate = 0;
    double timeConsumptionMatrix = 0;
    double timeCorrelation = 0;


    for (int i = 0; i < KEY_SIZE; i++) {
        // optimize first byte of each input data.
        dataSet.doCacheOptimization(i, 1);

        // do AES intermediate value
        AesSubBytesOutput aes = AesSubBytesOutput(&dataSet);
        printf("calculating intermediate values\n");
        begin = get_timestamp();
        IntermediateMatrix* intermediate = aes.doCryptoComputation();
        diff = double(get_timestamp() - begin) / 1000000.;
        timeIntermediate += diff;
        printf("Time -> %f\n", diff);

        // get consumption matrix
        printf("calculating consumption matrix\n");
        HWPowerModel powerModel = HWPowerModel(intermediate, PowerModel::RES_8_BITS);
        begin = get_timestamp();
        ConsumptionMatrix *matrix = powerModel.doPowerModel();
        diff = double(get_timestamp() - begin) / 1000000.;
        timeConsumptionMatrix += diff;
        printf("Time -> %f\n", diff);

        // calculate correlation coefficient (check double simple precision).
        printf("calculating correlation coefficient\n");
        CorrelationCoefficient corr = CorrelationCoefficient(matrix, &traceSet, floatPrecision == 2);
        begin = get_timestamp();
        ResultMatrix* res = corr.doStatisticalAnalysis();
        diff = double(get_timestamp() - begin) / 1000000.;
        timeCorrelation += diff;
        printf("Time -> %f\n", diff);


        // Check memory usage...
        double vm, rss;
        process_mem_usage(vm, rss);
        printf("VM: %f; RSS: %f; Total: %f\n", vm, rss, vm + rss);

        int keyPos, tracePos;
        double valuePos = res->getMaxValue(keyPos, tracePos);

        //cout << "\033[1;31mbold red text\033[0m\n";

        uint8_t key = *aes.getKeySet()->getElem(keyPos);
        cout << "\032[1;31mkey(" << i << ") = " << (int) key << " corr = " << valuePos << "\032[0m" << endl;

        res->toPng("correlation.png");
        delete intermediate;
        delete matrix;
        delete res;
    }

    printf("Total Intermediate: %f;\nTimeConsumptionMatrix: %f;\nTimeCorrelation: %f;\n",
            timeIntermediate, timeConsumptionMatrix, timeCorrelation);

    return 0;
}
