#!/bin/bash

rm pitch_${1}.dat
for X in A B C D E F G H I J
do
    for Y in 1 2 3 4 5 6 7 8 9
    do
	echo "${X}${Y}" >> pitch_${1}.dat
	./mapdreamchannels $1 ${X}${Y} | tail -1 >> pitch_${1}.dat
    done
done
