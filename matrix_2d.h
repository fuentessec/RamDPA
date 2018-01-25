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

