#!/usr/bin/env bash

cd bin
./prog -s 0123456788 -t 12345 -i 500 -e 12 -m -M > resultsThread.txt

./prog ./prog -s 0123456788 -i 500 -e 0 -m -M > resultsIter.txt
