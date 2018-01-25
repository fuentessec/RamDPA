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

