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
 * @file   KeyHipothesisSet.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent the DPA key hipotheis . 
 *
 * 
 */

#ifndef OPTIMIZEDKEYSET_H
#define OPTIMIZEDKEYSET_H

#include "binary_array_vector.h"
/**
 * @brief This class represents the set of key hypothesis of an DPA attack.
 */
class KeyHypothesisSet : public BinaryArrayVector{
    public:
        /**
         * Constructor method that generates an key hypothesis set with the specified size
         * and key size.
         * @param sizeKey key hypothesis size
         * @param numKeys Number of keys stored in the set.
         * @param random If true random keys will be added to the hypothesis set.
         */
    KeyHypothesisSet (unsigned int sizeKey, unsigned int numKeys,
                        bool random = false);
};


#endif /* OPTIMIZEDKEYSET_H */

