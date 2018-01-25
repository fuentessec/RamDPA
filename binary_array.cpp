/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"binary_array.h"
#include <random>

BinaryArray::BinaryArray(unsigned int sizeElem, bool random){
    this->sizeElem=sizeElem;
    
    this->value = std::shared_ptr<uint8_t> (new uint8_t [sizeElem], 
                [ ](uint8_t* p) { delete[ ] p; });
    
    if (random){
        std::random_device rd;

        for (unsigned int i= 0; i < sizeElem; i++){
            *(this->value.get()+i) = rd();
        }   
    }
}

BinaryArray::BinaryArray (unsigned int sizeElem, uint8_t* value, bool needsCopy){
    this->sizeElem = sizeElem;
        this->value = std::shared_ptr<uint8_t> (new uint8_t [sizeElem], 
                [ ](uint8_t* p) { delete[ ] p; });

        for (unsigned int i= 0; i < sizeElem; i++){
         *(this->value.get()+i) = value [i];

        }   
}


bool BinaryArray::writeData (uint8_t* buff, unsigned int ini, unsigned int len){
    if (ini + len > sizeElem)
        return false;

    for (unsigned int i = ini; i < len; i++){
        *(this->value.get()+i) = buff [i];
    }

    return true;
}

bool BinaryArray::readData (uint8_t* buff, unsigned int ini, unsigned int len) const{   
   if (ini + len > sizeElem)
        return false;
       
    for (unsigned int i = 0; i < len; i++){
        buff [i] = *(this->value.get()+i+ini);
    }

    return true;
}

uint8_t* BinaryArray::getPtr (){
    return this->value.get();
}

unsigned int BinaryArray::getSizeElement () const{
    return this->sizeElem;
}