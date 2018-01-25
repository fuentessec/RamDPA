/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "hw_power_model.h"
#include "intermediate.h"
#include <cstdint>

HWPowerModel::HWPowerModel (IntermediateMatrix *intermediateMatrix, 
        unsigned int resolution) : PowerModel (intermediateMatrix, resolution)
{}

uint32_t HWPowerModel::calculate (int inputDataPos, int keyHypothesisPos){
    uint8_t *elem = intermediateMatrix->
            getRawIntermediate(keyHypothesisPos, inputDataPos);
       
    uint32_t sum = 0;
    for (int i = 0; i < intermediateMatrix->getSizeIntermediate(); i++){
        sum += lookupTable [elem [i]];
    }
      
    return sum;
}

