/**
 * This class represents the set of key hypothesis (sub keys) of an DPA attack
 * which size is two byte.
 */

#ifndef CKEYHYPOTHESIS16SET_H
#define CKEYHYPOTHESIS16SET_H
#include "keyhypothesis_set.h"

/**
 * @brief This class represents the set of key hypothesis (sub keys) of 
 * an DPA attack which size is two bytes.
 * 
 */
class KeyHypothesis16Set : public KeyHypothesisSet
{
public:
    /**
     * Constructor method that generates an key hypothesis set with the specified size
     * and key size two byte.
     * @param numElems Number of keys stored in the set.
     */
    KeyHypothesis16Set(int numKeys);
};

#endif // CKEYHYPOTHESIS16SET_H
