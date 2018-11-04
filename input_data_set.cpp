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


InputDataSet::InputDataSet (unsigned int sizeElem, unsigned int num_elements)
{
    this->sizeElem = sizeElem;
    this->numElements = num_elements;

    for (unsigned int i = 0; i < num_elements; i++){
        dataset.push_back (InputData(sizeElem));
    }
}

bool InputDataSet::insertData (InputData value){
    if (this->sizeElem == value.getSizeElement()){
    numElements++;
    dataset.push_back(value);
    return true;
    }
    else{
        return false;
    }
}

InputData& InputDataSet::getData (unsigned int pos){
    return dataset [pos];
}

unsigned int InputDataSet::getNumElements (){
    return dataset.size();
}

bool InputDataSet::doCacheOptimization (unsigned int iniPos, unsigned int size,
                                            bool deleteInputData){
    bool res = true;
    
    if (cacheOpt != nullptr){
        delete [] cacheOpt;
    }
    
    this->cacheOpt = new uint8_t [size*numElements];
    this->sizeElemOpt = size;
    
    unsigned int offset = 0;
    for (int i = 0; i < dataset.size(); i++) {
        InputData aux = dataset.at(i);
        res &= aux.readData(cacheOpt + offset, iniPos, size);       
        offset += size;
    }
    
    if (deleteInputData){
        dataset.clear();
    }
    
    return res;
}

uint8_t* InputDataSet::getOptimizedData (unsigned int pos){
    if (pos > numElements){
        return nullptr;
    }else{
        return this->cacheOpt + (pos * this->sizeElemOpt);
    }
}

InputDataSet::~InputDataSet(){
        if (cacheOpt != nullptr){
        delete [] cacheOpt;
    }
}