#ifndef CPOWERMODEL_H
#define CPOWERMODEL_H

#include "intermediate_matrix.h"
#include "consumption_matrix.h"
#include <stdio.h>

/**
 * @brief Abstract class that represents the operation that takes as input an 
 * intermediate value and calculates its hypothetical power consumption.
 * 
 * This class generates a power consumption matrix from a intermediate matrix.
 * 
 * In case the integer environment variable NTHREADS is defined this operation will
 * be executed using as many threads as specified by such variable, improving the 
 * computation time.
 */
class PowerModel {
public:
    /// resolutions available
    static const int RES_8_BITS = 0;
    static const int RES_16_BITS = 1;
    static const int RES_32_BITS = 2;
    
    /**
     * 
     * @param intermediateMatrix Intermediate result matrix from where obtain
     * the intermediate results.
     * @param resolution Resolution required to generate the power consumption 
     * values.
     * This can get the next values: 8 bits (PowerModel::RES_8_BITS),
     * 16 bits (PowerModel::RES_16_BITS) and 32 bits (PowerModel::RES_32_BITS)
     * 
     */
    PowerModel (IntermediateMatrix *intermediateMatrix, unsigned int resolution);
    
    /**
     * This method calculates the hypothetical consumption of all the intermediate
     * results and generates a hypothetical consumption matrix.
     * 
     * This method may use multithreading if this options is specified through 
     * environment variables.
     * @return Hypothetical Consumption Matrix object. The owner of this object is the
     * caller, so deletion must be done by caller.
     */
    ConsumptionMatrix* doPowerModel ();
    
    /**
     * @return Reference to the intermediate result matrix provided
     * at construction time.
     */
    IntermediateMatrix* getIntermediateMatrix ();
protected:
    IntermediateMatrix* intermediateMatrix;
    ConsumptionMatrix* res;
    unsigned int keySize;
    unsigned int dataSize;
    unsigned int resolution;
    
    /**
     * /**
     * Abstract method. Subclasses must implement in this method the power consumption
     * model that given the position of the intermediate result
     *  is able to calculate the the hypothetical power consumption.  
     * @param inputDataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
     * @param keyHypothesisPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
     * @return the integer value that represents the hypothetical power consumption.
     */
    virtual uint32_t calculate (int inputDataPos, int keyHypothesisPos) = 0;
    
private:    
    // threading function
    void threadCalculation(int totalThreads, int numThread);
};

#endif /* CPOWERMODEL_H */

