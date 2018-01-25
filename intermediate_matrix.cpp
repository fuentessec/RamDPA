#include "intermediate_matrix.h"

IntermediateMatrix::IntermediateMatrix (unsigned int sizeKeyHypothesis, 
                        unsigned int sizeInputData,
                        unsigned int sizeIntermediate){
    this->values = new BinaryArrayMatrix (sizeIntermediate,sizeKeyHypothesis
            ,sizeInputData);
    
    this->keySize = sizeKeyHypothesis;
    this->dataSize = sizeInputData;
}

IntermediateMatrix::~IntermediateMatrix(){
    delete this->values;
}

bool IntermediateMatrix::setIntermediate (uint8_t* value, 
        int keyPos, int dataPos){
    
    return this->values->set(value, keyPos, dataPos);
}

Intermediate* IntermediateMatrix::getIntermediate (int keyPos, int dataPos){    
    return new Intermediate (values->getSizeElem(), 
            values->get(keyPos, dataPos), false);

}

uint8_t* IntermediateMatrix::getRawIntermediate (int keyPos, int dataPos){
    return values->get(keyPos, dataPos);
}

unsigned int IntermediateMatrix::getSizeKeyHypothesis (){
    return this->keySize;
}
unsigned int IntermediateMatrix::getSizeInputData (){
    return this->dataSize;
}

unsigned int IntermediateMatrix::getSizeIntermediate (){
    return this->values->getSizeElem();
}
