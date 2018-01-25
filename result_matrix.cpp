#include "result_matrix.h"
#include <float.h>
#include <iostream>

ResultMatrix::ResultMatrix(unsigned int sizeKeyHypothesis,
        unsigned int sizeTrace) {
    this->keySize = sizeKeyHypothesis;
    this->traceSize = sizeTrace;
}

unsigned int ResultMatrix::getSizeKeyHypothesis() {
    return this->keySize;
}

unsigned int ResultMatrix::getSizeTraceSet() {
    return this->traceSize;
}

double ResultMatrix::getMaxValue(int &keyPos, int &tracePos) {
    double maxValue = -DBL_MAX;

    for (int k = 0; k < keySize; k++) {
        for (int t = 0; t < traceSize; t++) {

            if (getResult(k, t) > maxValue) {
                maxValue = getResult(k, t);
                keyPos = k;
                tracePos = t;
            }
        }
    }

    return maxValue;
}

ResultMatrix32::ResultMatrix32(unsigned int sizeKeyHypothesis,
        unsigned int sizeTracesSet)
: ResultMatrix(sizeKeyHypothesis, sizeTracesSet) {
    this->values = new Matrix2D<float>(sizeKeyHypothesis, sizeTracesSet);
}

bool ResultMatrix32::setResult(double &value,
        int keyPos, int tracePos) {

    return this->values->set((float&) value, keyPos, tracePos);
}

double ResultMatrix32::getResult(int keyPos, int tracePos) {
    return this->values->get(keyPos, tracePos);
}

ResultMatrix32::~ResultMatrix32() {
    if (this->values != nullptr) {
        delete this->values;
    }
}

ResultMatrix64::ResultMatrix64(unsigned int sizeKeyHypothesis,
        unsigned int sizeTracesSet)
: ResultMatrix(sizeKeyHypothesis, sizeTracesSet) {
    this->values = new Matrix2D<double>(sizeKeyHypothesis, sizeTracesSet);
}

bool ResultMatrix64::setResult(double &value,
        int keyPos, int tracePos) {
    return this->values->set(value, keyPos, tracePos);
}

double ResultMatrix64::getResult(int keyPos, int tracePos) {
    return this->values->get(keyPos, tracePos);
}

ResultMatrix64::~ResultMatrix64() {
    if (this->values != nullptr) {
        delete this->values;
    }
}