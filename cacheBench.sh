#!/bin/bash
cp dist/Debug/GNU-Linux/doctorado .
sudo perf record -e cache-misses ./doctorado $1 $2 $3
sudo perf report --stdio | head -n $4

