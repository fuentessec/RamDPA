#include "crypto_computation.h"
#include <vector>
#include <thread>
#include <iostream>

#define MULTITHREAD

CryptoComputation::CryptoComputation(InputDataSet *dataSet,
        KeyHypothesisSet *keySet, unsigned int sizeElemIntermediate) {
    this->dataSet = dataSet;
    this->keySet = keySet;
    this->keySize = keySet->getNumElements();
    this->dataSize = dataSet->getNumElements();
    this->sizeElemIntermediate = sizeElemIntermediate;
}

IntermediateMatrix* CryptoComputation::doCryptoComputation() {

    res = new IntermediateMatrix(keySize,
            dataSize, sizeElemIntermediate);

#ifdef MULTITHREAD
    int num_threads = 1; // default value if NTHREADS environment variable is not defined

    if (getenv("NTHREADS"))
        num_threads = atoi(getenv("NTHREADS")); // number of threads as specified by NTHREADS.
    
    // create threads
    vector <thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(thread(&CryptoComputation::threadCalculation, this, num_threads, i));
    }


    // join threads and clean threads vector.
    for (int i = 0; i < num_threads; i++) {
        threads [i].join();
    }

    threads.clear();
#else
    for (int k = 0; k < keySize; k++) {
        for (int d = 0; d < dataSize; d++) {
            calculate(d, k);
        }
    }
#endif

    return res;
}

InputDataSet* CryptoComputation::getDataSet() {
    return this->dataSet;
}

KeyHypothesisSet* CryptoComputation::getKeySet() {
    return this->keySet;
}

void CryptoComputation::threadCalculation(int totalThreads, int numThread) {
//    for (int d = numThread; d < dataSize; d+= totalThreads) {
//        for (int k = 0; k < keySize; k++) { 
//            calculate(d, k);
//        }
//    }
    
    for (int k = numThread; k < keySize; k+=totalThreads) {
        for (int d = 0; d < dataSize; d++) { 
            calculate(d, k);
        }
    }
      
     
}