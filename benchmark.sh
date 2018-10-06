#!/bin/bash
# one thread with different trace resolutions
./doctorado 1 1 2 > ./benchResults/res112.txt
./doctorado 1 2 2 > ./benchResults/res122.txt
./doctorado 1 3 2 > ./benchResults/res132.txt
# two threads with different trace resolutions
./doctorado 2 1 2 > ./benchResults/res212.txt
./doctorado 2 2 2 > ./benchResults/res222.txt
./doctorado 2 3 2 > ./benchResults/res232.txt

# two threads with different trace resolutions
./doctorado 3 1 2 > ./benchResults/res312.txt
./doctorado 3 2 2 > ./benchResults/res322.txt
./doctorado 3 3 2 > ./benchResults/res332.txt

# two threads with different trace resolutions
./doctorado 4 1 2 > ./benchResults/res412.txt
./doctorado 4 2 2 > ./benchResults/res422.txt
./doctorado 4 3 2 > ./benchResults/res432.txt

# check float precision performance
./doctorado 4 2 1 > ./benchResults/res421.txt
./doctorado 4 2 2 > ./benchResults/res422.txt

