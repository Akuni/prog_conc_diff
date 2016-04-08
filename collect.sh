#!/usr/bin/env bash

cd bin
./prog -s 0123456789 -t 1 -i 500 -e 12 -m -M > ../resultsThread1.txt
./prog -s 0123456789 -t 2 -i 500 -e 12 -m -M > ../resultsThread2.txt
./prog -s 0123456789 -t 3 -i 500 -e 12 -m -M > ../resultsThread3.txt
./prog -s 0123456789 -i 500 -e 0 -m -M -t 1 > ../resultsIter.txt
./prog -s 0123456789 -t 4 -i 500 -e 12 -m -M > ../resultsThread4.txt
./prog -s 0123456789 -t 5 -i 500 -e 12 -m -M > ../resultsThread5.txt


