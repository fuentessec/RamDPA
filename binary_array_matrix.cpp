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


#include "binary_array_matrix.h"
#include "intermediate.h"


BinaryArrayMatrix::BinaryArrayMatrix(unsigned int sizeElem,
unsigned int sizeCols, unsigned int sizeRows){
    this->sizeCols = sizeCols;
    this->sizeRows = sizeRows;
    this->sizeElem = sizeElem;
    values = new uint8_t [sizeCols * sizeRows * sizeElem];
}

BinaryArrayMatrix::~BinaryArrayMatrix(){
    delete [] values;
}

uint8_t* BinaryArrayMatrix::get(unsigned int numCol, unsigned int numRow) {   
    // Stride-aware access, column-major order.
    return values+((sizeRows * numCol + numRow)*sizeElem); 
}

bool BinaryArrayMatrix::set(uint8_t* value, unsigned int numCol, unsigned int numRow) {
    if (numCol >= sizeCols || numRow >= sizeRows) {
        return false;
    }
    
    uint8_t* aux = get (numCol,numRow);
    for (int i = 0; i < sizeElem; i++) {
        *(aux++) = *(value++);
    }
    return true;
}

unsigned int BinaryArrayMatrix::getSizeCols (){
    return this->sizeCols;
}
unsigned int BinaryArrayMatrix::getSizeRows (){
    return this->sizeRows;
}
unsigned int BinaryArrayMatrix::getSizeElem (){
    return this->sizeElem;
}

