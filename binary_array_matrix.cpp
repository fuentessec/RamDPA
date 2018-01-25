#include "binary_array_matrix.h"
#include "intermediate.h"


BinaryArrayMatrix::BinaryArrayMatrix(unsigned int sizeElem,
unsigned int sizeCols, unsigned int sizeRows){
    this->sizeCols = sizeCols;
    this->sizeRows = sizeRows;
    this->sizeElem = sizeElem;
    values = new uint8_t [sizeCols * sizeRows * sizeElem];
}

BinaryArrayMatrix::~BinaryArrayMatrix(){
    delete [] values;
}

uint8_t* BinaryArrayMatrix::get(unsigned int numCol, unsigned int numRow) {   
    // Stride-aware access, column-major order.
    return values+((sizeRows * numCol + numRow)*sizeElem); 
}

bool BinaryArrayMatrix::set(uint8_t* value, unsigned int numCol, unsigned int numRow) {
    if (numCol >= sizeCols || numRow >= sizeRows) {
        return false;
    }
    
    uint8_t* aux = get (numCol,numRow);
    for (int i = 0; i < sizeElem; i++) {
        *(aux++) = *(value++);
    }
    return true;
}

unsigned int BinaryArrayMatrix::getSizeCols (){
    return this->sizeCols;
}
unsigned int BinaryArrayMatrix::getSizeRows (){
    return this->sizeRows;
}
unsigned int BinaryArrayMatrix::getSizeElem (){
    return this->sizeElem;
}

