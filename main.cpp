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

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}

int main() {
    timestamp_t begin;
    double diff;

    TraceSet traceSet = TraceSet();
    Trace *aux;

    // open traces file
    ifstream tracesFile("./traces/tracesRawIntPrint.txt");

    // read traces from file and create traceSet
    for (int i = 0; i < NUM_TRACES; i++) {
        Trace *aux = new Trace16(1000, 1.0 / 1024, -83.0 / 1024, TRACE_SIZE);
        for (int j = 0; j < TRACE_SIZE; j++) {
            uint16_t value;
            tracesFile >> value;
            aux->setValue(value, j);
        }
        traceSet.addTrace(aux);
    }

    /// PRINT TRACE INFO.
    //    ts1.getNTrace(0)->toPng("traceCHES2016.png");
    //    ts1.toPng("tracesCHES16.png");

    /// CHECK STATISTICS
    //    StatTrace *mean = ts1.meanTraces();
    //    StatTrace *variance = ts1.varianceTraces (mean);
    //    mean->toPng("tracesCHES16mean.png");
    //    variance->toPng("tracesCHES16var.png");

    // change traceset to statistical mode
    traceSet.statMode();


    // create data set
    InputDataSet dataSet = InputDataSet(DATA_SIZE);

    // read data file
    uint8_t auxData [16]; // aux array to hold data for InputData creation.
    ifstream dataFile("./traces/data.txt");
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

    for (int i = 0; i < KEY_SIZE; i++) {
        // optimize first byte of each input data.
        dataSet.doCacheOptimization(i, 1);

        // do AES intermediate value
        AesSubBytesOutput aes = AesSubBytesOutput(&dataSet);
        printf("calculating intermediate values\n");
        begin = get_timestamp();
        IntermediateMatrix* intermediate = aes.doCryptoComputation();
        diff = double(get_timestamp() - begin) / 1000000.;
        printf("Time -> %f\n", diff);

        // get consumption matrix
        printf("calculating consumption matrix\n");
        begin = get_timestamp();
        HWPowerModel powerModel = HWPowerModel(intermediate, PowerModel::RES_8_BITS);
        ConsumptionMatrix *matrix = powerModel.doPowerModel();
        diff = double(get_timestamp() - begin) / 1000000.;
        printf("Time -> %f\n", diff);

        // calculate correlation coefficient
        printf("calculating correlation coefficient\n");
        begin = get_timestamp();
        CorrelationCoefficient corr = CorrelationCoefficient(matrix, &traceSet);
        ResultMatrix* res = corr.doStatisticalAnalysis();
        diff = double(get_timestamp() - begin) / 1000000.;
        printf("Time -> %f\n", diff);


        int keyPos, tracePos;
        double valuePos = res->getMaxValue(keyPos, tracePos);

        //cout << "\033[1;31mbold red text\033[0m\n";

        uint8_t key = *aes.getKeySet()->getElem(keyPos);
        cout << "\032[1;31mkey(" << i << ") = " << (int) key << " corr = " << valuePos << "\032[0m" << endl;
        
        
        
        res->toPng("correlation.png");
    }
    return 0;
}
