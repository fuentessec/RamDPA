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


#ifndef RESULTMATRIZ_H
#define RESULTMATRIZ_H
#include "matrix_2d.h"
#include "interfaces.h"

class ResultMatrix : virtual public Graphicable{
public:
    ResultMatrix (unsigned int sizeKeyHypothesis, unsigned int sizeTrace);
    
    virtual bool setResult (double &value, int keyPos, int tracePos) = 0;
    virtual double getResult (int keyPos, int tracePos) = 0;
    
    double getMaxValue (int &keyPos, int &tracePos);
    
    virtual ~ResultMatrix() {}; // if not here subclass destructor not called.
    
    /**
     * 
     * @return Size of the key hypothesis set as specified at constructor. 
     */
    unsigned int getSizeKeyHypothesis ();
    
    /**
     * 
     * @return Size of the trace set as specified at constructor. 
     */
    unsigned int getSizeTraceSet ();
    
    int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
    
protected:
    unsigned int keySize;
    unsigned int traceSize;
};

class ResultMatrix32 : public ResultMatrix{
public:
    ResultMatrix32 (unsigned int sizeKeyHypothesis, unsigned int sizeTracesSet);
    bool setResult (double &value, int keyPos, int tracePos);
    double getResult (int keyPos, int tracePos);
    ~ResultMatrix32();
protected:
    Matrix2D<float> *values;
};

class ResultMatrix64 : public ResultMatrix{
    public:
    ResultMatrix64 (unsigned int sizeKeyHypothesis, unsigned int sizeTracesSet);
    bool setResult (double &value, int keyPos, int tracePos);
    double getResult (int keyPos, int tracePos);
    ~ResultMatrix64();
protected:
    Matrix2D<double> *values;
};


#endif /* RESULTMATRIZ_H */

