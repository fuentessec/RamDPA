/**
 * @file   BinaryArray.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent a vector of binary arrays. 
 */

#ifndef BINARYARRAYSET_H
#define BINARYARRAYSET_H

#include <cstdint>

/**
 * @brief This class represents a vector of byte arrays.
 * 
 * This class represents a vector of byte arrays. The size of such vectors must be the same 
 * for all vectors contained in the vector and must be known at construction time.
 */
class BinaryArrayVector {
public:
    /**
     * Constructor method that creates a vector of the specified dimensions for holding byte arrays
     * of the specified size. Arrays will be initialized to unknown value, use set to initialize them.
     * @param sizeElem Size of the byte arrays.
     * @param numElems Number of byte arrays that the vector contains.
     * @param random If true the byte arrays will be initialized with a random generator.
     */
    BinaryArrayVector (unsigned int sizeElem, unsigned int numElems,
                        bool random = false);
    
    /**
     * 
     * @return Number of byte arrays in vector.
     */
    unsigned int getNumElements ();
    
    /**
     * Method returns a reference to the array in the specified vector position.
     * @param pos Position in the vector where the array is.
     * @return Reference pointer to the selected array. Read the array bytes from this position.
     */
    uint8_t* getElem (int pos);
    
    /**
     * Method that writes an array in the specified vector position. This method will read
     * from value address as many bytes as the size of the array (as specified in constructor).
     * @param elem Initial address to bytes values from.
     * @param pos Position in the vector where the array will be written.
     */
    void setElem (uint8_t* elem, int pos);
    
    /**
     * Deletes all the arrays in the vector.
     */
    ~BinaryArrayVector();
private:
    unsigned int numElems;
    unsigned int sizeElem;
    uint8_t* values = nullptr;

};

#endif /* BINARYARRAYSET_H */

