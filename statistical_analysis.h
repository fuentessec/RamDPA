/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatisticalAnalysis.h
 * Author: alberto
 *
 * Created on September 17, 2017, 7:50 PM
 */

#ifndef STATISTICALANALYSIS_H
#define STATISTICALANALYSIS_H

#include "result_matrix.h"
#include "consumption_matrix.h"
#include "trace_set.h"

class StatisticalAnalysis {
public:
    
StatisticalAnalysis (ConsumptionMatrix *consumptionSet, TraceSet *traceSet,
            bool doublePrecision = true);

    ResultMatrix* doStatisticalAnalysis ();
    
    TraceSet* getTraceSet ();
    ConsumptionMatrix* getConsumptionSet ();

protected:
    TraceSet *traceSet;
    ConsumptionMatrix *consumptionSet;
    unsigned int keySize;
    unsigned int traceSize;
    bool doublePrecision;
    ResultMatrix * res;
    
    virtual void calculate (int keyHypothesisPos, int tracePos) = 0;
    
private:
    // threading function
    void threadCalculation(int totalThreads, int numThread);
};


#endif /* STATISTICALANALYSIS_H */

