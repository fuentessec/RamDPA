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

