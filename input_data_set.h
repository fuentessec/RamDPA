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
 * @file   inputdataset.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent a vector of binary arrays. 
 */
#ifndef CINPUTDATASET_H
#define CINPUTDATASET_H

#include "input_data.h"
#include <vector>
#include <cstdint>
using namespace std;

/**
 * @brief This class represents the set of input data of an DPA attack.
 */
class InputDataSet
{
public:
    /**
     * Constructor method that generates an input data set with the specified
     * element size. If the number of elements is specified, random elements will
     * be inserted at construction time.
     * @param sizeElem Size in bytes of the input data elements
     * @param num_elements Number of random inputs to be stored
     */
    InputDataSet (unsigned int sizeElem, unsigned int num_elements = 0);
    
    /**
     * Inserts a new input data element
     * @param value Element to be inserted.
     * @return 
     */
    bool insertData (InputData value);
    
    /**
     * This method returns a reference to the input data at the selected position.
     * @param pos position of the input data to be returned (starts at 0).
     * @return reference to the input data selected.
     */
    InputData& getData (unsigned int pos);
    
    /**
     * returns the memory address of the input data. This method can only be used
     * after cache optimization (see doCacheOptimization), so the input data will 
     * be reordered in memory to be cache-friendly.
     * @param pos position of the input data to be returned.
     * @return address of the input data after cache optimization.
     */
    uint8_t* getOptimizedData (unsigned int pos);
    
    /**
     * This method gets the part of the input data elements that will be used in
     * the DPA attack and copies it in a memory vector. This operation makes input
     * data cache optimized to be read consecutively.
     * @param iniPos Position of the input data elements from where information 
     * is important for DPA attack (in bytes).
     * @param size Bytes from iniPos which information is important for DPA attack
     * (in bytes).
     * @param deleteInputData If true, in order to memory efficiency, the input data
     * bytes that are outside (iniPos, iniPos+size) will be deleted.
     * @return True if operation succeeded.
     */
    bool doCacheOptimization (unsigned int iniPos, unsigned int size,
                                bool deleteInputData = false);
    
    /**
     * This method returns the number of input data elements in the set.
     * @return Number of input data elements in the set
     */
    unsigned int getNumElements ();
    ~InputDataSet ();
protected:
    unsigned int sizeElem;
    unsigned int numElements;
    unsigned int sizeElemOpt;
    vector<InputData> dataset;
    uint8_t *cacheOpt = nullptr;
};

#endif // CINPUTDATASET_H
