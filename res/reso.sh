#!/bin/bash

for X in 1 2 3 4 5 6 7 8
do
    cat D${X}/data/reso_*dat > D${X}/reso_${1}.dat
done
