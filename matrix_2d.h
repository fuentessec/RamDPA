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


#ifndef MATRIX2D_H
#define MATRIX2D_H
#include <vector>

using namespace std;

/**
 * @brief This class represents a 2D matrix of objects or primitive types.
 */
template <typename T>
class Matrix2D {
    std::vector<T> data;
    unsigned int sizeCol, sizeRow;
public:
    /**
     * Constructor that generates a matrix with the given dimensions.
     * @param numCol Number of columns
     * @param numRow Number of rows.
     */
    Matrix2D(unsigned int numCol, unsigned int numRow);

    /**
     * Method for getting a matrix element reference.
     * @param numCol Element column coordinate.
     * @param numRow Element row coordinate.
     * @return Reference to the selected element.
     */
    T& get(unsigned int numCol, unsigned int numRow);
    
    /**
     * Method for setting a matrix element.
     * @param value value to be set in the matrix
     * @param numCol Element column coordinate.
     * @param numRow Element row coordinate.
     * @return True if the operation succeeded.
     */
    bool set(T &value, unsigned int numCol, unsigned int numRow);
    
    
};

#endif /* MATRIX2D_H */

