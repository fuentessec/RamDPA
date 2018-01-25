#include "input_data.h"
#include <random>


using namespace std;

InputData::InputData(unsigned int sizeElem, bool random) : BinaryArray (sizeElem, random){}

InputData::InputData (unsigned int sizeElem, uint8_t* value, bool needsCopy) : BinaryArray (sizeElem, value, needsCopy){}

