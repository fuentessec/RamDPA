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


//#include "cscard.h"
#include "traceset.h"

#ifndef CTRACE
#include "trace.h"
#endif 

#ifndef CTIMESLICE
#include "ctimeslice.h"
#endif 

#include "keyhypothesisallvalues8set.h"
#include "keyhypothesisallvalues16set.h"
#include "Intermediate.h"
#include "intermediateMatrix.h"
#include "inputdataset.h"
#include "aesSubBytesOutput.h"
#include "consumptionmatrix.h"
#include "LBSPowerModel.h"
#include "HWPowerModel.h"
#include "BinaryArrayMatrix.h"
#include "CorrelationCoefficient.h"
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
/*
    uint8_t trc1_8 [] = {5, 100, 16, 89, 50, 20, 200, 90, 3};
    //uint8_t trc2_8 []=  {3,5,100,16,89,50,20,200,90};
    uint8_t trc2_8 [] = {100, 16, 89, 50, 20, 200, 90, 3, 5};
    uint16_t trc1_16 [] = {5, 100, 16, 89, 50, 20, 200, 90, 3};
    uint32_t trc1_32 [] = {5, 100, 16, 89, 50, 20, 200, 90, 3};

    uint8_t trc2 [] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t trc2disp [] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    /// Trace Testing.

    printf("--> CTrace\n");

    CTrace *t8 = new CTrace8(1000, 1.0, 0.0, trc1_8, 9);
    CTrace *t16 = new CTrace16(1000, 1.0, 0.0, trc1_16, 9);
    CTrace *t32 = new CTrace32(1000, 1.0, 0.0, trc1_32, 9);

    for (int i = 0; i < t8 -> size(); i++) {
        printf("%f, %f, %f\n", t8 -> getValue(i), t16 -> getValue(i), t32 -> getValue(i));
    }

    for (int i = 0; i < t16 -> size(); i++) {
        t8 -> setValue(i, i);
        t16 -> setValue(i * 2, i);
        t32 -> setValue(i * 3, i);
    }

    for (int i = 0; i < t32 -> size(); i++) {
        printf("%f, %f, %f\n", t8 -> getValue(i), t16 -> getValue(i), t32 -> getValue(i));
    }

    printf("%f\n", t8 -> getVoltConversion());

    t8 -> toPng("tests/test8.png");
    t16 -> toPng("tests/test16.png");
    t32 -> toPng("tests/test32.png");

    FILE *fd = fopen("tests/trace8.dat", "wb");
    FILE *fd2 = fopen("tests/trace16.dat", "wb");
    FILE *fd3 = fopen("tests/trace32.dat", "wb");
    t8 -> toDisk(fd);
    t16 -> toDisk(fd2);
    t32 -> toDisk(fd3);
    fclose(fd);
    fclose(fd2);
    fclose(fd3);

    fd = fopen("tests/trace8.dat", "rb");
    fd2 = fopen("tests/trace16.dat", "rb");
    fd3 = fopen("tests/trace32.dat", "rb");
    t8 -> fromDisk(fd);
    t16 -> fromDisk(fd2);
    t32 -> fromDisk(fd3);
    fclose(fd);
    fclose(fd2);
    fclose(fd3);

    t8 -> resize(t8 -> size() - 1);
    t16 -> resize(t16 -> size() - 1);
    t32 -> resize(t32 -> size() - 1);

    for (int i = 0; i < t16 -> size(); i++) {
        printf("%f, %f, %f\n", t8 -> getValue(i), t16 -> getValue(i), t32 -> getValue(i));
    }

    ///////// end of Trace testing

    //////// CTimeSlice testing
    printf("--> CTimeSlice\n");


    CTimeSlice *s8 = new CTimeSlice8(1.0, 0.0, trc1_8, 9);
    CTimeSlice *s16 = new CTimeSlice16(1.0, 0.0, trc1_16, 9);
    CTimeSlice *s32 = new CTimeSlice32(1.0, 0.0, trc1_32, 9);

    for (int i = 0; i < s8 -> size(); i++) {
        printf("%f, %f, %f\n", s8 -> getValue(i), s16 -> getValue(i), s32 -> getValue(i));
    }

    for (int i = 0; i < s16 -> size(); i++) {
        s8 -> setValue(i, i);
        s16 -> setValue(i * 2, i);
        s32 -> setValue(i * 3, i);
    }

    for (int i = 0; i < s32 -> size(); i++) {
        printf("%f, %f, %f\n", s8 -> getValue(i), s16 -> getValue(i), s32 -> getValue(i));
    }

    printf("%f\n", s8 -> getVoltConversion());

    s8 -> toPng("tests/test8_2.png");
    s16 -> toPng("tests/test16_2.png");
    s32 -> toPng("tests/test32_2.png");

    fd = fopen("tests/trace8.dat", "wb");
    fd2 = fopen("tests/trace16.dat", "wb");
    fd3 = fopen("tests/trace32.dat", "wb");
    s8 -> toDisk(fd);
    s16 -> toDisk(fd2);
    s32 -> toDisk(fd3);
    fclose(fd);
    fclose(fd2);
    fclose(fd3);

    fd = fopen("tests/trace8.dat", "rb");
    fd2 = fopen("tests/trace16.dat", "rb");
    fd3 = fopen("tests/trace32.dat", "rb");
    s8 -> fromDisk(fd);
    s16 -> fromDisk(fd2);
    s32 -> fromDisk(fd3);
    fclose(fd);
    fclose(fd2);
    fclose(fd3);

    for (int i = 0; i < s16 -> size(); i++) {
        printf("%f, %f, %f\n", s8 -> getValue(i), s16 -> getValue(i), s32 -> getValue(i));
    }

    ///////// end of TimeSlice testing

    //////// CTraceSet testing
    printf("--> CTraceSet\n");
    CTraceSet ts1 = CTraceSet();
    CTrace *aux, *auxt2;
    CTimeSlice *aux2;

    printf("-> TraceOps align mode\n");
    // add values to traceSet.
    for (int i = 0; i < 50; i++) {
        CTrace *aux = new CTrace8(1000, 1.0, 0.0, trc1_8, 9);
        ts1.addTrace(aux);
        aux = new CTrace8(1000, 1.0, 0.0, trc2_8, 9);
        ts1.addTrace(aux);
    }

    // get params traceSet
    printf("%d, %d\n", ts1.getLenTrace(), ts1.getLenSlice());

    // get Trace align mode
    aux = ts1.getNTrace(20);

    for (int i = 0; i < aux -> size(); i++) {
        printf("%f\n", aux -> getValue(i));
    }

    delete aux;

    aux = ts1.getNTraceRef(20);

    for (int i = 0; i < aux -> size(); i++) {
        printf("%f\n", aux -> getValue(i));
    }

    printf("-> SliceOps align mode\n");
    // get Slice align mode
    aux2 = ts1.getNSlice(3);

    printf("%d\n", aux2 -> size());

    for (int i = 0; i < aux2 -> size(); i++) {
        printf("%f\n", aux2 -> getValue(i));
    }

    delete aux2;

    aux2 = ts1.getNSliceRef(3);

    if (aux2)
        for (int i = 0; i < aux2-> size(); i++) {
            printf("%f\n", aux2 -> getValue(i));
        }

    ts1.toPng("tests/tracesetAlign.png");

    // statistical mode
    CTimeSlice *auxs, *auxs2;

    //////// preprocesors

    printf("-> preProcessors\n");

    CAlignSumTraceSet ts2 = CAlignSumTraceSet(3);

    for (int i = 0; i < ts1.getLenSlice(); i++) {
        ts2.addTrace(ts1.getNTrace(i));
    }

    ts2.preProcess();

    aux = ts2.getNTraceRef(0);

    for (int i = 0; i < aux -> size(); i++) {
        printf("%f\n", aux -> getValue(i));
    }

    CAlignMatchSqrTraceSet ts3 = CAlignMatchSqrTraceSet(2, 4, 4);

    for (int i = 0; i < ts1.getLenSlice(); i++) {
        ts3.addTrace(ts1.getNTrace(i));
    }

    ts3.preProcess();

    aux = ts3.getNTraceRef(0);
    auxt2 = ts3.getNTraceRef(1);

    for (int i = 0; i < aux -> size(); i++) {
        printf("%f %f\n", aux -> getValue(i), auxt2 -> getValue(i));
    }


    printf("-> TraceOps statistical mode\n");

    ts1.statMode();

    // get Trace Stat mode

    aux = ts1.getNTrace(15);

    for (int i = 0; i < aux -> size(); i++) {
        printf("%f\n", aux -> getValue(i));
    }

    delete aux;

    aux = ts1.getNTraceRef(15);

    if (aux)
        for (int i = 0; i < aux -> size(); i++) {
            printf("%f\n", aux -> getValue(i));
        }

    printf("-> SliceOps statistical mode\n");
    // get Slice Stat mode
    auxs2 = ts1.getNSlice(3);

    printf("%d\n", auxs2 -> size());

    for (int i = 0; i < auxs2 -> size(); i++) {
        printf("%f\n", auxs2 -> getValue(i));
    }

    delete auxs2;

    auxs2 = ts1.getNSliceRef(3);

    if (auxs2)
        for (int i = 0; i < auxs2-> size(); i++) {
            printf("%f\n", auxs2 -> getValue(i));
        }

    ts1.toPng("tests/tracesetStat.png");


    printf("mean & variance\n");
    CStatTrace *stat = ts1.varianceTraces();

    for (int i = 0; i < stat -> size(); i++) {
        printf("%f ", stat -> getValue(i));
    }
    printf("\n");
    delete stat;


    stat = ts1.meanTraces();

    for (int i = 0; i < stat -> size(); i++) {
        printf("%f ", stat -> getValue(i));
    }
    printf("\n");

    CStatTrace *stat2 = ts1.varianceTraces();


    fd = fopen("tests/stats.dat", "wb");
    stat2 -> toDisk(fd);
    fclose(fd);

    fd = fopen("tests/stats.dat", "rb");
    stat2 -> fromDisk(fd);
    fclose(fd);

    for (int i = 0; i < stat2 -> size(); i++) {
        printf("%f ", stat2 -> getValue(i));
    }
    printf("\n");

    delete stat;
    delete stat2;

    ///////// end of CTraceSet testing

    ///////// CKeyhypothesis



    printf("creating key8set\n");
    begin = get_timestamp();
    CKeyHypothesisAllValues8Set key8set;
    diff = double( get_timestamp() - begin) / 1000000.;
    printf("AllValues8Set -> %f\n", diff);

    for (unsigned int i = 0; i <= 255; i++) {
        uint8_t value;
        key8set.getData(i).readData((uint8_t*) & value, 0, 1);
        cout << "value key = " << value << endl;
    }

    printf("creating key16set\n");
    begin = get_timestamp();
    CKeyHypothesisAllValues16Set key16set;
    diff = double( get_timestamp() - begin) / 1000000.;
    printf("AllValues16Set -> %f\n", diff);
    for (unsigned int i = 0; i <= 0xFFFF; i++) {
        u_int16_t value;
        key16set.getData(i).readData((uint8_t*) & value, 0, 2);
        cout << "value key = " << value << endl;
    }

    /////////// intermediate
    uint8_t *value = new uint8_t [10];
    memset(value, 'a', 10);
    CIntermediate *intermediate = new CIntermediate(10, value);
    cout << "Intermediate size = " << intermediate -> getSizeElement() << endl;
    delete intermediate;



    /// intermediate Matrix
    CIntermediateMatrix intMatrix(8, 8);


    uint8_t value2 = 'a';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            CIntermediate *aux = new CIntermediate(1, &value2);
            intMatrix.setIntermediate(*aux, i, j);
            value2++;
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            uint8_t aux;
            CIntermediate inter = intMatrix.getIntermediate(i, j);
            inter.readData(&aux, 0, inter.getSizeElement());
            cout << aux << endl;
        }
    }
*/  

    /*
    CKeyHypothesisSet* keySet = aes.getKeySet();
    
    uint8_t result, data, key;
    for (int k = 0; k < 256; k++){
        for (int i = 0; i < INPUT_SIZE; i++){
            intermediate->getIntermediate(k,i).readData(&result, 0,1);
            keySet->getData(k).readData(&key, 0, 1);
            dataSet.getData(i).readData(&data,0,1);
            cout <<  std::hex << "data: " << (int)data << " key: " << (int)key << " inter: " << (int)result <<endl;
        }
    }  
     */
    
/*
#define INPUT_SIZE 100
    CInputDataSet dataSet = CInputDataSet(1, INPUT_SIZE);
    dataSet.doCacheOptimization(0,1);
    
    AesSubBytesOutput aes = AesSubBytesOutput(&dataSet);
    

    printf("calculating intermediate values\n");
    begin = get_timestamp();
    CIntermediateMatrix* intermediate2 = aes.doCryptoComputation();
    diff = double(get_timestamp() - begin) / 1000000.;
    printf("Time -> %f\n", diff);
    delete intermediate2;
   */ 
    
    /*
    CConsumptionMatrix8 consumptionMatrix = CConsumptionMatrix8 (16,16);
    
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++) {
            unsigned int value = i;
            cout <<  value << std::endl;
            consumptionMatrix.setConsumption(value, i, j);
        }
    }
    
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++) {
            unsigned int value = i*j;
            cout <<  consumptionMatrix.getConsumption(i,j) << std::endl;
        }
    }
    */
    
        /*
    BinaryArray binaryArray = BinaryArray (20);
    int numElem = binaryArray.getSizeElement();
    
    uint8_t* aux = new uint8_t [numElem];
    
    binaryArray.readData (aux, 0, 20);
    
    for (int i = 0; i < numElem; i++) {
         cout << std::hex << (int)aux [i] << std::endl;
    }
    
    uint8_t* aux2 = binaryArray.getPtr();
    
    for (int i = 0; i < numElem; i++) {
         cout << std::hex << (int)(*aux2++) << std::endl;
    }
    
    BinaryArray binaryArray2 = BinaryArray (20,binaryArray.getPtr(), true);
    
    binaryArray2.readData (aux, 0, 20);
    
    cout << std::hex << "binaryArray2" << std::endl;
    
    for (int i = 0; i < numElem; i++) {
         cout << std::hex << (int)aux [i] << std::endl;
    }

    delete [] aux;
    */
    
    /// TEST FROM INPUT TO CONSUMPTION.
    /*
    #define INPUT_SIZE 100
    #define PRINT
    InputDataSet dataSet = InputDataSet(1, INPUT_SIZE);
    
    printf("Creating crypto algorithm\n");
    
    AesSubBytesOutput aes = AesSubBytesOutput(&dataSet);
    
    printf("cache optimization\n");
    
    dataSet.doCacheOptimization(0,1);

    printf("calculating intermediate values\n");
    begin = get_timestamp();
    IntermediateMatrix* intermediate2 = aes.doCryptoComputation();
    diff = double(get_timestamp() - begin) / 1000000.;
    printf("Time crypto compt -> %f\n", diff);
    
#ifdef PRINT
    printf("print values 1\n");
    for (int i = 0; i < intermediate2->getSizeInputData(); i++) {
        for (int j = 0; j < intermediate2->getSizeKeyHypothesis(); j++) {
            Intermediate *aux = intermediate2->getIntermediate(j,i);
            uint8_t value;
            aux->readData(&value, 0, 1);
            cout << std::hex << (int)value << " "; 
            delete aux;
        }
    }
#endif
    printf("\n\nconsumption model\n");
    HWPowerModel powerModel = HWPowerModel (intermediate2, PowerModel::RES_8_BITS);
    begin = get_timestamp();
    ConsumptionMatrix *matrix = powerModel.doPowerModel();
    diff = double(get_timestamp() - begin) / 1000000.;
    printf("Time power model -> %f\n", diff);
#ifdef PRINT
    for (int i = 0; i < matrix->getSizeInputData(); i++) {
        for (int j = 0; j < matrix->getSizeKeyHypothesis(); j++) {
            Intermediate *aux = intermediate2->getIntermediate(j,i);
            uint8_t value;
            aux->readData(&value, 0, 1);
            delete aux;
            
            uint32_t value2 = matrix->getConsumption(j,i);
            cout << std::hex << (int)value << " -> " <<  (int)value2 << std::endl;
        }
    }
#endif
    
    delete matrix;
    delete intermediate2;
     */
    
    /*
#define NUMROWS 10
#define NUMCOLS 5
    BinaryArrayMatrix test = BinaryArrayMatrix (4, NUMCOLS, NUMROWS);
    
    uint32_t value = 0;
    for (int col = 0; col < NUMCOLS; col++) {
        for (int row = 0; row < NUMROWS; row++) {
            test.set((uint8_t*)&value, col, row);
            value++;
        }
    }
    
    for (int col = 0; col < NUMCOLS; col++) {
        for (int row = 0; row < NUMROWS; row++) {
            uint32_t* value2 = (uint32_t*) test.get(col, row);
            cout << value2 << " : " << *value2 << " row: " << row << " col: " << col << endl;
        }
    }

*/
  /*
    /// TEST CORRELATION
#define NUM_DATA 6
#define NUM_KEY 6
#define SIZE_TRACE 5
    uint16_t tracesExample [NUM_DATA][SIZE_TRACE] =  
    {{1, 10, 8, 2, 50},
    {2, 3, 5, 4, 3},
    {3, 70, 5, 8, 20},
    {4, 13, 5, 16, 3},
    {5, 10000, 5, 32, 9},
    {5, 10000, 5, 32, 9}};
    
    uint16_t consExample[NUM_DATA][NUM_KEY] =  
    {{65,4,3,2,12,1},
    {4,25,7,88,34,234},
    {6,9,3, 69,100,34},
    {100,103,3,39,5,5},
    {3,1000,3,1,234,64},
    {20, 10000, 5, 32,342,46}};
                        
    
    
    printf("--> CTraceSet\n");
    TraceSet ts1 = TraceSet();
    ConsumptionMatrix *matrix = new ConsumptionMatrix16 (NUM_KEY, NUM_DATA);
    Trace *aux, *auxt2;
    TimeSlice *aux2;

    // add values to traceSet.
    for (int i = 0; i < NUM_DATA; i++) {
        Trace *aux = new Trace16(1000, 1.0, 0.0, tracesExample[i], SIZE_TRACE);
        ts1.addTrace(aux);
    }
    
    // add values to consumptionMatrix
    for (int i = 0; i < NUM_DATA; i++) {
        for (int j = 0; j < NUM_KEY; j++){
            uint32_t value = consExample [i][j];
            matrix->setConsumption(value, j, i);
        } 
    }
    
    ts1.statMode();
    
    // correlation calculation.
    
    CorrelationCoefficient corr = CorrelationCoefficient(matrix, &ts1);
    ResultMatrix* res = corr.doStatisticalAnalysis();
      
    
    for (int i = 0; i < SIZE_TRACE; i++) {
        for (int j = 0; j < NUM_KEY; j++) {
           cout << "Slice = " << i << " key = " << j << " correlation = " 
                   << res->getResult(j, i) << endl;
        }
    }
    
    int key, slice;
    double max = res->getMaxValue(key, slice);
    
    cout << "Max = " << max << " => " << " key = " << key << "slice = " << slice << endl;
    
    delete matrix;
    delete res;
   */
     
    return 0;
}
