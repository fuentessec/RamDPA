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

