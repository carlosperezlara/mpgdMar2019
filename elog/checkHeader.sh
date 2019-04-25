#!/bin/bash

rm runs.dat.evt.cel.p906
for X in `awk {'print $1'} runs.dat.evt.num`
do
    ddump -t9 -p906  ../data/beam/beam-$X-0000.evt >> runs.dat.evt.cel.p906
    ddump -t12 -p906 ../data/beam/beam-$X-0000.evt >> runs.dat.evt.cel.p906
done
