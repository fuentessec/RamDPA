#ifndef CINTERMEDIATE_H
#define CINTERMEDIATE_H

#include <cstdint>
#include <memory>
#include <vector>
#include "binary_array.h"

/**
 * @brief Class that represents the intermediate result in DPA attack.
 */
class Intermediate : public BinaryArray {
public:
    /**
     * Constructor to create an intermediate value.
     * @param sizeElem Intermediate value size in bytes.
     * @param value Memory position where bytes are.
     * @param needsCopy If true, a copy of the memory values will be done, in other case
     * input data will store a reference to the memory position.
     */
    Intermediate (unsigned int sizeElem, uint8_t* value, bool needsCopy);
protected:
};

#endif /* CINTERMEDIATE_H */

