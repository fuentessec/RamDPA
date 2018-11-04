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


#ifndef CINTERMEDIATE_H
#define CINTERMEDIATE_H

#include <cstdint>
#include <memory>
#include <vector>
#include "binary_array.h"

/**
 * @brief Class that represents the intermediate result in DPA attack.
 */
class Intermediate : public BinaryArray {
public:
    /**
     * Constructor to create an intermediate value.
     * @param sizeElem Intermediate value size in bytes.
     * @param value Memory position where bytes are.
     * @param needsCopy If true, a copy of the memory values will be done, in other case
     * input data will store a reference to the memory position.
     */
    Intermediate (unsigned int sizeElem, uint8_t* value, bool needsCopy);
protected:
};

#endif /* CINTERMEDIATE_H */

