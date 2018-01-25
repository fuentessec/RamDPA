/**
 * This class represents the set of key hypothesis (sub keys) of an DPA attack
 * which size is one byte.
 */

#ifndef CKEYHYPOTHESIS8SET_H
#define CKEYHYPOTHESIS8SET_H
#include "keyhypothesis_set.h"

/**
 * @brief This class represents the set of key hypothesis (sub keys) of 
 * an DPA attack which size is one byte.
 * 
 */
class KeyHypothesis8Set : public KeyHypothesisSet
{
public:
    /**
     * Constructor method that generates an key hypothesis set with the specified size
     * and key size one byte.
     * @param numElems Number of keys stored in the set.
     */
    KeyHypothesis8Set(int numKeys);
};

#endif // CKEYHYPOTHESIS8SET_H
