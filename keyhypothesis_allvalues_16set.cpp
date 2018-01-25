#include "keyhypothesis_allvalues_16set.h"
#include <stdint.h>

KeyHypothesisAllValues16Set::KeyHypothesisAllValues16Set() : KeyHypothesis16Set (65536)
{
    // insert all values in the set
    for (uint16_t i = 0; i <= 0xFFFF; i++){
        setElem ((uint8_t*)&i, i);
    }
}
