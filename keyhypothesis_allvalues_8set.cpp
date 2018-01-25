#include "keyhypothesis_allvalues_8set.h"
#include <stdint.h>


KeyHypothesisAllValues8Set::KeyHypothesisAllValues8Set() : KeyHypothesis8Set (256)
{
    // insert all values in the set
    for (uint16_t i = 0; i <= 0x0FF; i++){
        setElem ((uint8_t*)&i, i);
    }
}
