/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "consumption_matrix.h"

ConsumptionMatrix::ConsumptionMatrix (unsigned int sizeKeyHypothesis, 
                            unsigned int sizeInputData){
    this->keySize = sizeKeyHypothesis;
    this->dataSize = sizeInputData;
}

unsigned int ConsumptionMatrix::getSizeKeyHypothesis (){
    return this->keySize;
}
unsigned int ConsumptionMatrix::getSizeInputData (){
    return this->dataSize;
}

ConsumptionMatrix32::ConsumptionMatrix32 (unsigned int sizeKeyHypothesis, 
        unsigned int sizeInputData) 
        : ConsumptionMatrix (sizeKeyHypothesis, sizeInputData){
    this->values = new Matrix2D<uint32_t>(sizeKeyHypothesis, sizeInputData);
}

bool ConsumptionMatrix32::setConsumption (uint32_t &value, 
        int keyPos, int dataPos){
    
    return this->values->set(value, keyPos, dataPos);
}

uint32_t ConsumptionMatrix32::getConsumption (int keyPos, int dataPos){    
    return this->values->get(keyPos,dataPos);
}

ConsumptionMatrix32::~ConsumptionMatrix32(){
    if (this->values != nullptr){
        delete this->values;
    }
}

ConsumptionMatrix16::ConsumptionMatrix16 (unsigned int sizeKeyHypothesis, 
                                                unsigned int sizeInputData)
                        : ConsumptionMatrix (sizeKeyHypothesis, sizeInputData){
    this->values = new Matrix2D<uint16_t>(sizeKeyHypothesis, sizeInputData);
}
bool ConsumptionMatrix16::setConsumption (uint32_t &value, int keyPos, int dataPos){
    // check if truncation is possible.

    if (value < 0x0FFFF){
       return this->values->set((uint16_t&)value, keyPos, dataPos);
    }else{
        return false;
    }
}

uint32_t ConsumptionMatrix16::getConsumption (int keyPos, int dataPos){
    return this->values->get(keyPos,dataPos);
}

ConsumptionMatrix16::~ConsumptionMatrix16(){
    if (this->values != nullptr){
        delete this->values;
    }
}


ConsumptionMatrix8::ConsumptionMatrix8 (unsigned int sizeKeyHypothesis, 
                                            unsigned int sizeInputData)
                        : ConsumptionMatrix (sizeKeyHypothesis, sizeInputData){
    this->values = new Matrix2D<uint8_t>(sizeKeyHypothesis, sizeInputData);
}

bool ConsumptionMatrix8::setConsumption (uint32_t &value, int keyPos, int dataPos){
    if (value < 0x0FF){
        return this->values->set((uint8_t&)value, keyPos, dataPos);
    }else{
        return false;
    }
}

uint32_t ConsumptionMatrix8::getConsumption (int keyPos, int dataPos){
    return this->values->get(keyPos,dataPos);
}

ConsumptionMatrix8::~ConsumptionMatrix8(){
    if (this->values != nullptr){
        delete this->values;
    }
}