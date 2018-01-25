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

int ResultMatrix::toPng(char *fileName, list<string> *gnuplotCmds) {
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe <= 0) {
        return -1;
    }

    int keyBest, tracePos;
    getMaxValue(keyBest, tracePos);

    // send commands to gnuplot
    fprintf(gnuplotPipe, "set terminal png\n"); // output as png
    fprintf(gnuplotPipe, "set title\"Correlation key (%d)\"\n", keyBest); // output as png
    fprintf(gnuplotPipe, "set output \"%s\"\n ", fileName); // output name
    fprintf(gnuplotPipe, "set xlabel \"Correlation\"\n"); // set x label
    fprintf(gnuplotPipe, "set ylabel \"Time\"\n"); // set y label

    //send added commands to gnuplot
    if (gnuplotCmds)
        for (list<string>::iterator it = gnuplotCmds->begin(); it != gnuplotCmds->end(); it++)
            fprintf(gnuplotPipe, "%s\n", it->data()); // print nth command.

    fprintf(gnuplotPipe, "plot '-' using ($1 / %lld.):2 notitle with lines\n", 1); // set scale and representation mode

    // send data to gnuplot

    for (size_t t = 0; t < this->traceSize; t++) {
        fprintf(gnuplotPipe, "%lld %f\n", t, getResult(keyBest, t));
    }


    // metadata for "end of data"
    fprintf(gnuplotPipe, "e");

    // close gnuplot interface
    fprintf(gnuplotPipe, "\n");
    fprintf(gnuplotPipe, "exit \n");
    fflush(gnuplotPipe);

    // free memory and structures.
    fclose(gnuplotPipe);
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