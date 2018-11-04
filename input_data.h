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


/**
 * @file   BinaryArray.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent the DPA input data. 
 *
 * 
 */

#ifndef CINPUTDATA_H
#define CINPUTDATA_H
#include <cstdint>
#include "binary_array.h"


/**
 * @brief The class represents the DPA input data (plaintext or ciphertext).
 * 
 * The class represents the DPA input data (plaintext or ciphertext). InputData is
 * a binary array of fixed size.
 */
class InputData : public BinaryArray {
public:
    /**
     * Constructor to create an input data with undefined or random value (i.e. to be sent 
     * to the crypto device).
     * @param sizeElem Input data size in bytes.
     * @param random If true random value will be assigned to the bytes of the input data.
     */
    InputData(unsigned int sizeElem, bool random = true);
    
    /**
     * Constructor to create an Input data 
     * @param sizeElem Input data size in bytes.
     * @param value Memory position where bytes are.
     * @param needsCopy If true, a copy of the memory values will be done, in other case
     * input data will store a reference to the memory position.
     */
    InputData (unsigned int sizeElem, uint8_t* value, bool needsCopy);
};

#endif // CINPUTDATA_H
