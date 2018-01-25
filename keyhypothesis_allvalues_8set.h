#ifndef CKEYHYPOTHESISALLVALUES8SET_H
#define CKEYHYPOTHESISALLVALUES8SET_H

#include "keyhypothesis_8set.h"

/**
 * @brief This class represents the set of all the key hypothesis (sub keys) of 
 * an DPA attack which size is one byte.
 * 
 * Keys will contain all the possible values [0, 2⁸)
 */

class KeyHypothesisAllValues8Set : public KeyHypothesis8Set
{
public:
     /**
     * Constructor method that generates a key hypothesis set with all possible
     * one byte key values. 
     */
    KeyHypothesisAllValues8Set();
};

#endif // CKEYHYPOTHESISALLVALUESSET_H
