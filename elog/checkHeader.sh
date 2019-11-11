#!/bin/bash

#rm runs.dat.evt.cel.p906
for X in `awk {'print $1'} runs.dat.evt.num`
do
    ddump -t9 -p940  ../data/beam/beam-$X-0000.evt > jpg/run$X-p940.jpg
    #ddump -t9 -p906  ../data/beam/beam-$X-0000.evt >> runs.dat.evt.cel.p906
    #ddump -t12 -p906 ../data/beam/beam-$X-0000.evt >> runs.dat.evt.cel.p906
    #
    #rm aquaconf/run_${X}.p907
    #ddump -t9 -p907  ../data/beam/beam-$X-0000.evt >> aquaconf/run_${X}.p907
    #ddump -t12 -p907 ../data/beam/beam-$X-0000.evt >> aquaconf/run_${X}.p907
done
