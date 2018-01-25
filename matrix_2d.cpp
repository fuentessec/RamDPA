#include "matrix_2d.h"
#include "intermediate.h"

template<typename T>
Matrix2D<T>::Matrix2D(unsigned int numCol, unsigned int numRow)
: sizeCol(numCol), sizeRow(numRow) {
    data.resize(sizeCol * sizeRow);
}

template<typename T>
T& Matrix2D<T>::get(unsigned int numCol, unsigned int numRow) {   
    return data[sizeRow * numCol + numRow]; // Stride-aware access
}

template<typename T>
bool Matrix2D<T>::set(T &value, unsigned int numCol, unsigned int numRow) {
    if (numCol >= sizeCol || numRow >= sizeRow) {
        return false;
    }

    data[sizeRow * numCol + numRow] = value;
    return true;
}

template class Matrix2D<uint32_t>;
template class Matrix2D<uint16_t>;
template class Matrix2D<uint8_t>;
template class Matrix2D<float>;
template class Matrix2D<double>;



