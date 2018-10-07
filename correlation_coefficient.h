

#ifndef CORRELATIONCOEFFICIENT_H
#define CORRELATIONCOEFFICIENT_H
#include "statistical_analysis.h"

class CorrelationCoefficient : public StatisticalAnalysis{
public:
    CorrelationCoefficient (ConsumptionMatrix *consumptionSet, TraceSet *traceSet,
        bool doublePrecision = true);
        
protected:
    vector <double> traceMeans;
    vector <double> consumptionMeans;
    void calculate (int keyHypothesisPos, int tracePos);
};

#endif /* CORRELATIONCOEFFICIENT_H */

