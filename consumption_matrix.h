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


#ifndef CCONSUMPTIONMATRIX_H
#define CCONSUMPTIONMATRIX_H

#include "matrix_2d.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Abstract class that represents the hypothetical consumption 
 * matrix in DPA attacks.
 */
class ConsumptionMatrix{
public:
    /**
     * Consumption matrix constructor. Memory for this structure will be reserved
     * at construction time.
     * @param sizeKeyHypothesis Number of key hypothesis. 
     * @param sizeInputData Number of input data elements.
     */
    ConsumptionMatrix (unsigned int sizeKeyHypothesis, unsigned int sizeInputData);
    
    /**
     * This method writes an consumption value 
     * into the matrix in the specified position. 
     * @param value reference to the consumption value.
     * @param keyPos Key hypothesis position used to generate the power consumption
     * result (defines the matrix column position). 
     * @param dataPos Input data position used to generate the power consumption
     * result. (defines the matrix row position). 
     * @return True if the operation succeeded
     */
    virtual bool setConsumption (uint32_t &value, int keyPos, int dataPos) = 0;
    
    /**
     * This method returns a consumption element from the consumption matrix.
     * @param keyPos Key hypothesis position used to generate the power consumption
     * result (defines the matrix column position). 
     * @param dataPos Input data position used to generate the power consumption
     * result. (defines the matrix row position). 
     * @return Consumption element in the specified matrix position.
     */
    virtual uint32_t getConsumption (int keyPos, int dataPos) = 0;
    virtual ~ConsumptionMatrix() {}; // if not here subclass destructor not called.
    
    /**
     * 
     * @return Size of the key hypothesis set as specified at constructor. 
     */
    unsigned int getSizeKeyHypothesis ();
    
    /**
     * 
     * @return Size of the input data set as specified at constructor. 
     */
    unsigned int getSizeInputData ();

protected:
    unsigned int keySize;
    unsigned int dataSize;
};

/**
 * @brief Implementation of ConsumptionMatrix with 32 bits of resolution.
 */
class ConsumptionMatrix32 : public ConsumptionMatrix{
public:
    /**
     * Consumption matrix constructor. Memory for this structure will be reserved 
     * at construction time. Matrix elements have a resolution of 32 bits.
     * @param sizeKeyHypothesis Number of key hypothesis. 
     * @param sizeInputData Number of input data elements. 
     */
    ConsumptionMatrix32 (unsigned int sizeKeyHypothesis, unsigned int sizeInputData);
    
    /**
     * This method writes an consumption value into the matrix in the specified position.
     * @param value reference to the consumption value. 
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return True if operation succeeded.
     */
    bool setConsumption (uint32_t &value, int keyPos, int dataPos);
    
    /**
     * This method returns a consumption element from the consumption matrix.
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return Consumption element in the specified matrix position.
     */
    uint32_t getConsumption (int keyPos, int dataPos);
    ~ConsumptionMatrix32();
protected:
    Matrix2D<uint32_t> *values;
};

/**
 * @brief Implementation of ConsumptionMatrix with 16 bits of resolution.
 */
class ConsumptionMatrix16 : public ConsumptionMatrix{
public:
    /**
     * Consumption matrix constructor. Memory for this structure will be reserved 
     * at construction time. Matrix elements have a resolution of 16 bits.
     * @param sizeKeyHypothesis Number of key hypothesis. 
     * @param sizeInputData Number of input data elements. 
     */
    ConsumptionMatrix16 (unsigned int sizeKeyHypothesis, unsigned int sizeInputData);
    
     /**
     * This method writes an consumption value into the matrix in the specified position.
     * The value must fit in a 16 bit unsigned integer.
     * @param value reference to the consumption value. 
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return True if operation succeeded.
     */
    bool setConsumption (uint32_t &value, int keyPos, int dataPos);
    
     /**
     * This method returns a consumption element from the consumption matrix.
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return Consumption element in the specified matrix position.
     */
    uint32_t getConsumption (int keyPos, int dataPos);
    ~ConsumptionMatrix16();
protected:
    Matrix2D<uint16_t> *values;
};

/**
 * @brief Implementation of ConsumptionMatrix with 8 bits of resolution.
 */
class ConsumptionMatrix8 : public ConsumptionMatrix{
public:
        /**
     * Consumption matrix constructor. Memory for this structure will be reserved 
     * at construction time. Matrix elements have a resolution of 8 bits.
     * @param sizeKeyHypothesis Number of key hypothesis. 
     * @param sizeInputData Number of input data elements. 
     */
    ConsumptionMatrix8 (unsigned int sizeKeyHypothesis, unsigned int sizeInputData);
    
     /**
     * This method writes an consumption value into the matrix in the specified position.
     * The value must fit in a 8 bit unsigned integer.
     * @param value reference to the consumption value. 
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return True if operation succeeded.
     */
    bool setConsumption (uint32_t &value, int keyPos, int dataPos);
    
     /**
     * This method returns a consumption element from the consumption matrix.
     * @param keyPos Key hypothesis position used to generate the power consumption 
     * result (defines the matrix column position).
     * @param dataPos Input data position used to generate the power consumption 
     * result. (defines the matrix row position). 
     * @return Consumption element in the specified matrix position.
     */
    uint32_t getConsumption (int keyPos, int dataPos);
    ~ConsumptionMatrix8();
protected:
    Matrix2D<uint8_t> *values;
};

#endif /* CCONSUMPTIONMATRIX_H */

