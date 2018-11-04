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

