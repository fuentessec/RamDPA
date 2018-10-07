#include "correlation_coefficient.h"
#include <math.h>
#include <iostream>

CorrelationCoefficient::CorrelationCoefficient (ConsumptionMatrix *consumptionSet,
        TraceSet *traceSet,
        bool doublePrecision) : StatisticalAnalysis (consumptionSet,
                                                            traceSet,
                                                            doublePrecision)
{

    // calculate means once, so they do not have to be calculated several times
    // during calculation
    traceMeans.resize (traceSize);
    consumptionMeans.resize(keySize);
    
    int sizeData = consumptionSet->getSizeInputData();
    
    double mean;
    for (int i = 0; i < traceSize; i++){
        mean = 0;
        TimeSlice* traceSlice = traceSet->getNSliceRef(i);
        for (int j = 0; j < sizeData; j++){
            mean += traceSlice->getRawValue(j);
        }
        traceMeans[i] = mean / traceSlice->size();
    }
    
    for (int i = 0; i < keySize; i++){
        mean = 0;
        for (int j = 0; j < sizeData; j++){
            mean += consumptionSet->getConsumption(i, j);
        }
        consumptionMeans[i] = mean / consumptionSet->getSizeInputData();
    }
}

void CorrelationCoefficient::calculate (int keyHypothesisPos, int tracePos){
    // obtain the trace slice
    TimeSlice* traceSlice = traceSet->getNSliceRef(tracePos);
    
    // first calculate the mean for consumption and trace.
    double consumptionMean = 0, traceMean = 0;
    
    int sizeData = consumptionSet->getSizeInputData();
    
    // get means from vectors initilizated at constructor
    consumptionMean = consumptionMeans[keyHypothesisPos];
    traceMean = traceMeans[tracePos];
    
    /*
    // key mean
    for (int i = 0; i < sizeData; i++){
        consumptionMean += consumptionSet->getConsumption(keyHypothesisPos, i);
    }
       
    consumptionMean /= consumptionSet->getSizeInputData();
    
    // trace mean
    for (int i = 0; i < sizeData; i++){
        traceMean += traceSlice->getRawValue(i);
    }
     
    
    traceMean /= traceSlice->size();
    
     */ 
    // get correlation coefficient numerator, squared difference
    double numerator = 0;
    double sumSquareDiffConsumption = 0;
    double sumSquareDiffTrace = 0;
    
    for (int i = 0; i < sizeData; i++){
        /// differences calculation (h(d,i) - mean (h)) and (t(d,j)-mean(t))
        double consumptionDiff = consumptionSet->getConsumption(keyHypothesisPos, i)- consumptionMean;
        double traceDiff = traceSlice->getRawValue(i) - traceMean;
        
        numerator += consumptionDiff*traceDiff;
        
        /// sum of squared differences consumptions
        sumSquareDiffConsumption +=  consumptionDiff*consumptionDiff;
        
        /// sum of squared differences trace values
        sumSquareDiffTrace += traceDiff*traceDiff;
    }
    
    // final correlation calculation
    double corr = numerator / sqrt (sumSquareDiffConsumption*sumSquareDiffTrace);
    
    if (corr < 0){
        corr = -corr;
    }
    
    // debug
    /*
    std::cout << "==== K = " << keyHypothesisPos << ", S = " << tracePos << std::endl;
    std::cout << "Media consumption = " << consumptionMean << 
            ", Media slice = " << traceMean << std::endl;
    
    std::cout << "SumSquareDiffConsumption = " << sumSquareDiffConsumption <<
            ", sumSquareDiffTrace = " << sumSquareDiffTrace << std::endl;
    
    std::cout << "sqtr() = " << sqrt (sumSquareDiffConsumption*sumSquareDiffTrace) << std::endl;
    
    std::cout << "res = " << corr << std::endl;
     */
    
    /// set absolute value of correlation

    this->res->setResult(corr, keyHypothesisPos, tracePos);

    
    
}
