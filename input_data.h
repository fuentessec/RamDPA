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
