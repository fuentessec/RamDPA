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

