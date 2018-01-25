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

