#!/bin/bash
cp dist/Debug/GNU-Linux/doctorado .
sudo perf record -e cache-references,cache-misses ./doctorado $1 $2 $3
sudo perf report --stdio | grep -E "CorrelationCoefficient|Event"

