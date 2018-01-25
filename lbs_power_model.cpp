/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "lbs_power_model.h"
#include "intermediate.h"


LBSPowerModel::LBSPowerModel (IntermediateMatrix *intermediateMatrix, 
        unsigned int resolution) : PowerModel (intermediateMatrix, resolution)
{}

uint32_t LBSPowerModel::calculate (int inputDataPos, int keyHypothesisPos){
    uint8_t *LByte = intermediateMatrix->
            getRawIntermediate(keyHypothesisPos, inputDataPos);
    
    
    
    // get least significant byte.
    LByte += intermediateMatrix->getSizeIntermediate()-1;
        
    if ((*LByte) % 2 == 0){
        return 0;
    }else{
        return 1;
    }
}

