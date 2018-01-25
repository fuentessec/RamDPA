#include "aes_sub_bytes_output.h"
#include "keyhypothesis_allvalues_8set.h"
#include "intermediate_matrix.h"
#include <cstdint>

AesSubBytesOutput::AesSubBytesOutput(InputDataSet *dataSet) : 
CryptoComputation (dataSet, new KeyHypothesisAllValues8Set(), 1)
{}

/// this operation is byte oriented take one byte from dataSet and key.
void AesSubBytesOutput::calculate (int inputDataPos, 
        int keyHypothesisPos){
    
    uint8_t* data = dataSet->getOptimizedData (inputDataPos);
    //CKeyHypothesis keyHypothesis = this->keySet->getData(keyHypothesisPos);

    uint8_t* key = this->keySet->getElem(keyHypothesisPos);
    
    // addRoundKey
    uint8_t intermediate;
    intermediate = (*data) ^ (*key);
    
    // subBytes (pre-calculated).
    intermediate = sbox[intermediate];
    
    res->setIntermediate(&intermediate, keyHypothesisPos, inputDataPos);
}

AesSubBytesOutput::~AesSubBytesOutput(){
    delete keySet;
}

