/**
 * @file   KeyHipothesisSet.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @brief  This file contains a class to represent the DPA key hipotheis . 
 *
 * 
 */

#ifndef OPTIMIZEDKEYSET_H
#define OPTIMIZEDKEYSET_H

#include "binary_array_vector.h"
/**
 * @brief This class represents the set of key hypothesis of an DPA attack.
 */
class KeyHypothesisSet : public BinaryArrayVector{
    public:
        /**
         * Constructor method that generates an key hypothesis set with the specified size
         * and key size.
         * @param sizeKey key hypothesis size
         * @param numKeys Number of keys stored in the set.
         * @param random If true random keys will be added to the hypothesis set.
         */
    KeyHypothesisSet (unsigned int sizeKey, unsigned int numKeys,
                        bool random = false);
};


#endif /* OPTIMIZEDKEYSET_H */

