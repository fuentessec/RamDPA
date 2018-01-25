/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "power_model.h"
#include <vector>
#include <thread>
#include <iostream>
#define MULTITHREAD

PowerModel::PowerModel (IntermediateMatrix *intermediateMatrix, unsigned int resolution){
    this->intermediateMatrix = intermediateMatrix;
    this->keySize = intermediateMatrix->getSizeKeyHypothesis();
    this->dataSize = intermediateMatrix->getSizeInputData();
    this->resolution = resolution;
}

ConsumptionMatrix* PowerModel::doPowerModel (){   
    switch (this->resolution){
        case RES_8_BITS:
            res = new ConsumptionMatrix8(keySize, dataSize);
            break;
        case RES_16_BITS:
            res = new ConsumptionMatrix16(keySize, dataSize);
            break;
        default:
            res = new ConsumptionMatrix32(keySize, dataSize);
    }
    
    
    
    
    #ifdef MULTITHREAD
    int num_threads = 1; // default value if NTHREADS environment variable is not defined

    if (getenv("NTHREADS"))
        num_threads = atoi(getenv("NTHREADS")); // number of threads as specified by NTHREADS.
    
    std::cout << "threads " << num_threads << std::endl;

    // create threads
    vector <thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(thread(&PowerModel::threadCalculation, this, num_threads, i));
    }


    // join threads and clean threads vector.
    for (int i = 0; i < num_threads; i++) {
        threads [i].join();
    }

    threads.clear();
#else
    for (int k = 0; k < keySize; k++) {
        for (int d = 0; d < dataSize; d++) {
            uint32_t aux = calculate(d, k);
            res->setConsumption(aux, k, d);
        }
    }
#endif
    
    return res;
}
    
IntermediateMatrix* PowerModel::getIntermediateMatrix (){
    return this->intermediateMatrix;
}


void PowerModel::threadCalculation(int totalThreads, int numThread){
    
//    for (int d = numThread; d < dataSize; d+= totalThreads) {
//        for (int k = 0; k < keySize; k++) { 
//            uint32_t aux = calculate(d, k);
//            res->setConsumption(aux, k, d);
//        }
//    }
    
    for (int k = numThread; k < keySize; k+= totalThreads) {
        for (int d = 0; d < dataSize; d++) { 
            uint32_t aux = calculate(d, k);
            res->setConsumption(aux, k, d);
        }
    }
    
}
