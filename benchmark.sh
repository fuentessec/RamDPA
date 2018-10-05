#!/bin/bash
# one thread with different trace resolutions
./doctorado 1 1 2 > ./benchResults/res112.txt
./doctorado 1 2 2 > ./benchResults/res122.txt
./doctorado 1 3 2 > ./benchResults/res132.txt
# two threads with different trace resolutions
./doctorado 2 1 2 > ./benchResults/res212.txt
./doctorado 2 2 2 > ./benchResults/res222.txt
./doctorado 2 3 2 > ./benchResults/res232.txt

# check float precision performance
./doctorado 2 2 1 > ./benchResults/res221.txt
./doctorado 2 2 2 > ./benchResults/res222.txt

