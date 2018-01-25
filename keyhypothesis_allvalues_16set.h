/**
 * This class represents the set of all the key hypothesis (sub keys) of 
 * an DPA attack which size is two byte. Keys will contain all the possible
 * values [0, 2¹⁶)
 */

#ifndef CKEYHYPOTHESISALLVALUES16SET_H
#define CKEYHYPOTHESISALLVALUES16SET_H

#include "keyhypothesis_16set.h"

/**
 * @brief This class represents the set of all the key hypothesis (sub keys) of 
 * an DPA attack which size is two byte. 
 * 
 * Keys will contain all the possible values [0, 2⁸)
 */
class KeyHypothesisAllValues16Set : public KeyHypothesis16Set
{
public:
    /**
     * Constructor method that generates a key hypothesis set with all possible
     * two byte key values. 
     */
    KeyHypothesisAllValues16Set();
};

#endif // CKEYHYPOTHESISALLVALUESSET_H
