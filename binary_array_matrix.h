/**
 * @file   BinaryArray.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent a matrix of binary arrays. 
 *
 * 
 */

#ifndef BINARYARRAYMATRIX_H
#define BINARYARRAYMATRIX_H

#include <vector>
#include <cstdint>

using namespace std;

/**
 * @brief This class represents a matrix of byte vectors.
 * 
 * The size of such vectors must be the same 
 * for all vectors contained in the matrix and must be known at construction time.
 */

class BinaryArrayMatrix {
public:
    /**
     * Constructor method that creates a matrix of the specified dimensions for holding byte vectors
     * of the specified size. Vectors will be initialized to unknown value, use set to initialize them.
     * @param sizeElem size of the byte vectors.
     * @param sizeCols number of matrix columns.
     * @param sizeRows number of matrix rows.
     */
    BinaryArrayMatrix(unsigned int sizeElem, 
            unsigned int sizeCols, unsigned int sizeRows);
    
    /**
     * This method will free the memory that contains the elements inserted in the matrix.
     */
    ~BinaryArrayMatrix ();

    /**
     * Method returns a reference to the vector in the specified matrix position. Use 
     * getSizeElem to know the length of the vector.
     * @param numCol Column where the vector is.
     * @param numRow Row where the vector is.
     * @return Reference pointer to the selected vector. Read the vector bytes from this position.
     * Use getSizeElem to know the vector's size.
     */
    uint8_t* get(unsigned int numCol, unsigned int numRow);
    
    /**
     * Method that writes a vector in the specified matrix position. This method will read
     * from value address as many bytes as the size of the vectors (as specified in constructor). 
     * @param value Initial address to read values from.
     * @param numCol Column where the vector is.
     * @param numRow Row where the vector is.
     * @return true If operation succeeded
     */
    bool set(uint8_t* value, unsigned int numCol, unsigned int numRow);
    
    /**
     * 
     * @return Number of columns in matrix.
     */
    unsigned int getSizeCols ();
    
    /**
     * 
     * @return Number of rows in matrix.
     */
    unsigned int getSizeRows ();
    
    /**
     * 
     * @return Size of the byte vectors (in bytes).
     */
    unsigned int getSizeElem ();
private:
    uint8_t* values = nullptr;
    unsigned int sizeCols, sizeRows;
    unsigned int sizeElem;
    
};

#endif /* BINARYARRAYMATRIX_H */

