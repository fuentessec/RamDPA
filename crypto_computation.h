#include "input_data_set.h"
#include "keyhypothesis_set.h"
#include "intermediate.h"
#include "intermediate_matrix.h"

#ifndef CCRYPTOCOMPUTATION_H
#define CCRYPTOCOMPUTATION_H

/**
 * @brief abstract class that represents the operation that takes as inputs the key 
 * hypothesis and the input data and generates the intermediate results of a DPA attack.
 * 
 * In case the integer environment variable NTHREADS is defined this operation will
 * be executed using as many threads as specified by such variable, improving the 
 * computation time.
 */
class CryptoComputation {
public:
    /**
     * Cryptographic operation constructor that receives the input data set and 
     * hypothetical key set. Also the size of the cryptographic output
     * (intermediate values) must be provided.
     * 
     * @param dataSet Pointer to the InputDataSet to be used in the cryptographic
     * calculation.
     * @param keySet Pointer to the hypothetical key set to be used in the
     * cryptographic calculation
     * @param sizeElemIntermediate Intermediate result size in bytes produced by
     * the cryptographic operation.
     */
    CryptoComputation (InputDataSet *dataSet, KeyHypothesisSet *keySet,
            unsigned int sizeElemIntermediate);
    
    
    IntermediateMatrix* doCryptoComputation ();
    
    /**
     * 
     * @return Reference to the input data set given at construction time.
     */
    InputDataSet* getDataSet ();
    
    /**
     * 
     * @return Reference to the hypothetical key set given at construction time.
     */
    KeyHypothesisSet* getKeySet ();
    
protected:
    InputDataSet *dataSet;
    KeyHypothesisSet *keySet;
    unsigned int keySize;
    unsigned int dataSize;
    unsigned int sizeElemIntermediate;
    IntermediateMatrix * res;
    /// this method does the crypto calculation
    /**
     * Abstract method. Subclasses must implement in this method the cryptographic
     * operation that given the position in the input data set (POS_I) and key 
     * hypothesis set (POS_K) is able to write the cryptographic result in the 
     * protected attribute res in position (POS_I, POS_K).
     * @param inputDataPos Input data position in the input data set.
     * @param keyHypothesisPos Key hypothesis position in the key hypothesis set.
     */
    virtual void calculate (int inputDataPos, int keyHypothesisPos) = 0;
    
private:
    // threading function
    void threadCalculation(int totalThreads, int numThread);
};

#endif /* CCRYPTOCOMPUTATION_H */

