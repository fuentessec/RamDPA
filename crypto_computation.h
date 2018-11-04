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

