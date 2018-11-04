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


#include "binary_array_vector.h"
#include <random>

BinaryArrayVector::BinaryArrayVector (unsigned int sizeElem, unsigned int numElems,
                        bool random){
    this->numElems = numElems;
    this->sizeElem = sizeElem;
    this->values = new uint8_t [numElems*sizeElem];
    
    if (random){
        std::random_device rd;
        for (unsigned int i= 0; i < numElems*sizeElem; i++){
            *(values+i) = rd();
        }   
    }
}


unsigned int BinaryArrayVector::getNumElements (){
    return numElems;
}


uint8_t* BinaryArrayVector::getElem (int pos){
    return values+(pos*sizeElem);
}


void BinaryArrayVector::setElem (uint8_t* elem, int pos){
    uint8_t* aux = getElem (pos);
    
    for (int i = 0; i < sizeElem; i++) {
        *(aux++) = *(elem++);
    }
}

BinaryArrayVector::~BinaryArrayVector(){
    if (values != nullptr){
        delete [] values;
    }
}

