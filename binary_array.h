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
 * @brief  This file represents a vector of bytes. 
 *
 * BinaryArray class can create random byte arrays. If initialized from values in memory
 * in the constructor can be specified if the object will contain a reference to those values
 * or create a copy.
 * 
 * 
 */

#ifndef BINARYARRAY_H
#define BINARYARRAY_H

#include <cstdint>
#include <memory>

/**
 * @brief This class represents a vector of bytes. 
 */

class BinaryArray {
    public:
    /**
     *  This constructor creates a vector of bytes of the specified size. If random is true
     * the vector will be initialized with random values.
     * 
     * @param sizeElem Size of the created vector of bytes.
     * @param random If true vector will be initialized with random values.
     * 
     */
    BinaryArray(unsigned int sizeElem, bool random = true);
    
    /**
     *  Constructor to create a vector of bytes with the bytes given at the specified memory position.
     *
     * @param sizeElem Size of the created vector of bytes.
     * @param value Pointer to the memory position where bytes are.
     * @param needsCopy If true a copy memory of the values will be done, in other case, 
     * the vector will be a reference to that memory position.
     * 
     * 
     */
    BinaryArray (unsigned int sizeElem, uint8_t* value, bool needsCopy);

    /**
     * Write bytes to the specified position.
     * @param buff Pointer to the memory position where bytes to be written to the vector
     * are.
     * @param ini Initial position in vector to be written (first position 0).
     * @param len Number of consecutive bytes to be written.
     */
    bool writeData (uint8_t* buff, unsigned int ini, unsigned int len);
    
    /**
     * Reads bytes from the specified position
     * @param buff Pointer to the memory position where bytes will be written.
     * @param ini Initial position in vector to be read from (first position 0).
     * @param len Number of consecutive bytes to be read.
     * 
     * @return True if operation succeeded
     */
    bool readData (uint8_t* buff, unsigned int ini, unsigned int len) const;
    
    /**
     * Returns a pointer to the vector's initial position.
     * @return Address of the vector's initial position.
     */
    uint8_t* getPtr ();
    
    /**
     * Size of bytes in the byte vector.
     * @return Size of bytes in the byte vector.
     */
    unsigned int getSizeElement () const;

protected:
    unsigned int sizeElem;
    std::shared_ptr<uint8_t> value; 
};

#endif /* BINARYARRAY_H */

