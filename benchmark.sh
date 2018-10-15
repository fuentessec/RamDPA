#!/bin/bash
# one thread with different trace resolutions
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 1 1 2 > ./benchResults/res112.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 1 2 2 > ./benchResults/res122.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 1 3 2 > ./benchResults/res132.txt
# two threads with different trace resolutions
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 2 1 2 > ./benchResults/res212.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 2 2 2 > ./benchResults/res222.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 2 3 2 > ./benchResults/res232.txt

# two threads with different trace resolutions
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 3 1 2 > ./benchResults/res312.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 3 2 2 > ./benchResults/res322.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 3 3 2 > ./benchResults/res332.txt

# two threads with different trace resolutions
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 4 1 2 > ./benchResults/res412.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 4 2 2 > ./benchResults/res422.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 4 3 2 > ./benchResults/res432.txt

# check float precision performance
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 4 2 1 > ./benchResults/res421.txt
sudo perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./doctorado 4 2 2 > ./benchResults/res422.txt

