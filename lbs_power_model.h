/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LBSPowerModel.h
 * Author: alberto
 *
 * Created on June 28, 2017, 11:26 PM
 */

#ifndef LBSPOWERMODEL_H
#define LBSPOWERMODEL_H

#include "power_model.h"
#include <cstdint>

/**
 * @brief Power Model operation which assumption is that consumption increases when
 * the lower bit of the intermediate value is set to one.
 * 
 */
class LBSPowerModel : public PowerModel {
    public:
        /**
         * See PowerModel constructor.
         * @param intermediateMatrix
         * @param resolution
         */
        LBSPowerModel (IntermediateMatrix *intermediateMatrix, unsigned int resolution);
    protected:
        /**
         * Override of PowerModel::calculate. It returns 1 if the intermediate value
         * lower bit is set to 1 and 0 otherwise.
         * @param inputDataPos Input data position used to generate the intermediate result.
     * (defines the matrix row position).
         * @param keyHypothesisPos Key hypothesis position used to generate the intermediate result
     * (defines the matrix column position).
         * @return It returns 1 if the intermediate value 
         * lower bit is set to 1 and 0 otherwise.
         */
        uint32_t calculate (int inputDataPos, int keyHypothesisPos);
        
};

#endif /* LBSPOWERMODEL_H */

