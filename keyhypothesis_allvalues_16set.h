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
 * This class represents the set of all the key hypothesis (sub keys) of 
 * an DPA attack which size is two byte. Keys will contain all the possible
 * values [0, 2¹⁶)
 */

#ifndef CKEYHYPOTHESISALLVALUES16SET_H
#define CKEYHYPOTHESISALLVALUES16SET_H

#include "keyhypothesis_16set.h"

/**
 * @brief This class represents the set of all the key hypothesis (sub keys) of 
 * an DPA attack which size is two byte. 
 * 
 * Keys will contain all the possible values [0, 2⁸)
 */
class KeyHypothesisAllValues16Set : public KeyHypothesis16Set
{
public:
    /**
     * Constructor method that generates a key hypothesis set with all possible
     * two byte key values. 
     */
    KeyHypothesisAllValues16Set();
};

#endif // CKEYHYPOTHESISALLVALUESSET_H
