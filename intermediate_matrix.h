#include "intermediate.h"
#include "binary_array_matrix.h"

#ifndef CINTERMEDIATEMATRIX_H
#define CINTERMEDIATEMATRIX_H

/**
 * @brief Class that represents the intermediate result matrix in DPA attack.
 * 
 */
class IntermediateMatrix{
public:
    /**
     * Intermediate value matrix constructor. Memory for this structure will be 
     * reserved at construction time.
     * @param sizeKeyHypothesis Number of key hypothesis.
     * @param sizeInputData Number of input data elements.
     * @param sizeIntermediate Size in bytes of the intermediate result as result
     * of the cryptographic operation.
     */
    IntermediateMatrix (unsigned int sizeKeyHypothesis, 
                        unsigned int sizeInputData,
                        unsigned int sizeIntermediate);
    
    /**
     * This method writes an intermediate result into the matrix in the specified
     * position.
     * @param value Memory address that contains the intermediate result. The size
     * of the intermediate element to read is specified at construction time 
     * (sizeIntermediate). Bytes will be copied into the matrix.
     * @param keyPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
     * @param dataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
     * @return True if operation succeeded.
     */
    bool setIntermediate (uint8_t* value, int keyPos, int dataPos);
    
    /**
     * Method to get an intermediate result form the matrix. Do not use this method
     * for optimized computation.
     * @param keyPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
     * @param dataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
     * @return Intermediate value copied from the matrix. The owner of this object is
     * the caller, so it need to be freed by it.
     */
    Intermediate *getIntermediate (int keyPos, int dataPos);
    
    /**
     * Method to get an intermediate result form the matrix. It returns a memory
     * reference to the element, use it for optimized computation. Elements in matrix
     * are ordered to be read increasing the dataPos. In that way reads are cache-friendly.
     * @param keyPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
     * @param dataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
     * @return Memory address from where read the intermediate result.
     */
    uint8_t *getRawIntermediate (int keyPos, int dataPos);
    
    /**
     * 
     * @return Size of the key hypothesis set as specified at constructor.
     */
    unsigned int getSizeKeyHypothesis ();
    
    /**
     * 
     * @return Size of the input data set as specified at constructor.
     */
    unsigned int getSizeInputData ();
    
    /**
     * 
     * @return Intermediate result size in bytes.
     */
    unsigned int getSizeIntermediate ();
    ~IntermediateMatrix();
protected:
    BinaryArrayMatrix *values;
    unsigned int keySize;
    unsigned int dataSize;
};

#endif /* CINTERMEDIATEMATRIX_H */

