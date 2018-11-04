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

/* 
 * File:   LBSPowerModel.h
 * Author: alberto
 *
 * Created on June 28, 2017, 11:26 PM
 */

#ifndef LBSPOWERMODEL_H
#define LBSPOWERMODEL_H

#include "power_model.h"
#include <cstdint>

/**
 * @brief Power Model operation which assumption is that consumption increases when
 * the lower bit of the intermediate value is set to one.
 * 
 */
class LBSPowerModel : public PowerModel {
    public:
        /**
         * See PowerModel constructor.
         * @param intermediateMatrix
         * @param resolution
         */
        LBSPowerModel (IntermediateMatrix *intermediateMatrix, unsigned int resolution);
    protected:
        /**
         * Override of PowerModel::calculate. It returns 1 if the intermediate value
         * lower bit is set to 1 and 0 otherwise.
         * @param inputDataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
         * @param keyHypothesisPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
         * @return It returns 1 if the intermediate value 
         * lower bit is set to 1 and 0 otherwise.
         */
        uint32_t calculate (int inputDataPos, int keyHypothesisPos);
        
};

#endif /* LBSPOWERMODEL_H */

