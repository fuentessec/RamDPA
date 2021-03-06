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
 * File:   HDPowerModel.h
 * Author: alberto
 *
 * Created on June 29, 2017, 12:12 PM
 */

#ifndef HDPOWERMODEL_H
#define HDPOWERMODEL_H

#include "power_model.h"

/**
 * 
 * @brief Power Model operation which assumption is that consumption increases linearly
 * with the value's number of 1's.
 */
class HWPowerModel : public PowerModel {
    public:
        /**
         * See PowerModel constructor.
         * @param intermediateMatrix
         * @param resolution
         */
        HWPowerModel (IntermediateMatrix *intermediateMatrix, unsigned int resolution);
    protected:
        /**
         * Override of PowerModel::calculate. It returns the number of 1's present
         * in the binary representation of the intermediate value.
         * @param inputDataPos Input data position used to generate the intermediate result.
         * (defines the matrix row position).
         * @param keyHypothesisPos Key hypothesis position used to generate the intermediate result
         * (defines the matrix column position).
         * @return It returns the number of 1's present 
         * in the binary representation of the intermediate value
         */
        uint32_t calculate (int inputDataPos, int keyHypothesisPos);
    private:
            
        uint8_t lookupTable [256] = 
        {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
         1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
         1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
         2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
         1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
         2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
         2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
         3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8};
        


        
};




#endif /* HDPOWERMODEL_H */

