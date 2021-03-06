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


#include "statistical_analysis.h"
#include <vector>
#include <thread>

#define MULTITHREAD

StatisticalAnalysis::StatisticalAnalysis(ConsumptionMatrix *consumptionSet,
        TraceSet *traceSet,
        bool doublePrecision) {
    this->traceSet = traceSet;
    this->consumptionSet = consumptionSet;
    this->keySize = consumptionSet->getSizeKeyHypothesis();
    this->traceSize = traceSet->getLenTrace();
    this->doublePrecision = doublePrecision;
}

TraceSet* StatisticalAnalysis::getTraceSet() {
    return traceSet;
}

ConsumptionMatrix* StatisticalAnalysis::getConsumptionSet() {
    return consumptionSet;
}

ResultMatrix* StatisticalAnalysis::doStatisticalAnalysis() {
    if (doublePrecision) {
        res = new ResultMatrix64(keySize, traceSize);
    } else {
        res = new ResultMatrix32(keySize, traceSize);
    }

#ifdef MULTITHREAD
    int num_threads = 1; // default value if NTHREADS environment variable is not defined

    if (getenv("NTHREADS"))
        num_threads = atoi(getenv("NTHREADS")); // number of threads as specified by NTHREADS.

    // create threads
    vector <thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(thread(&StatisticalAnalysis::threadCalculation, this, num_threads, i));
    }

    // join threads and clean threads vector.
    for (int i = 0; i < num_threads; i++) {
        threads [i].join();
    }

    threads.clear();
#else
    for (int k = 0; k < keySize; k++) {
        for (int t = 0; t < traceSize; t++) {
            calculate(k, t);
        }
    }
#endif

    return res;
}

void StatisticalAnalysis::threadCalculation(int totalThreads, int numThread) { 
        for (int t = 0; t < traceSize; t+=totalThreads) { 
            for (int k = numThread; k < keySize; k++) {
            calculate(k, t);
        }
    }
}