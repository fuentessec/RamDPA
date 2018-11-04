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


#include "intermediate_matrix.h"

IntermediateMatrix::IntermediateMatrix (unsigned int sizeKeyHypothesis, 
                        unsigned int sizeInputData,
                        unsigned int sizeIntermediate){
    this->values = new BinaryArrayMatrix (sizeIntermediate,sizeKeyHypothesis
            ,sizeInputData);
    
    this->keySize = sizeKeyHypothesis;
    this->dataSize = sizeInputData;
}

IntermediateMatrix::~IntermediateMatrix(){
    delete this->values;
}

bool IntermediateMatrix::setIntermediate (uint8_t* value, 
        int keyPos, int dataPos){
    
    return this->values->set(value, keyPos, dataPos);
}

Intermediate* IntermediateMatrix::getIntermediate (int keyPos, int dataPos){    
    return new Intermediate (values->getSizeElem(), 
            values->get(keyPos, dataPos), false);

}

uint8_t* IntermediateMatrix::getRawIntermediate (int keyPos, int dataPos){
    return values->get(keyPos, dataPos);
}

unsigned int IntermediateMatrix::getSizeKeyHypothesis (){
    return this->keySize;
}
unsigned int IntermediateMatrix::getSizeInputData (){
    return this->dataSize;
}

unsigned int IntermediateMatrix::getSizeIntermediate (){
    return this->values->getSizeElem();
}
