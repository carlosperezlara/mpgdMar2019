#!/bin/bash

GROUP=0;
echo "NOTHING" > tmp.tmp

for X in `awk {'print $1'} runs.dat.evt.num`
do
    diff aquaconf/run_${X}.p907 tmp.tmp > tmp2.tmp
    if [ -f tmp2.tmp ]
    then
	if [ -s tmp2.tmp ]
	then
	    cp aquaconf/run_${X}.p907 group_${GROUP}_${X}.txt
	    cp aquaconf/run_${X}.p907 tmp.tmp
	    let "GROUP +=1"
	fi
    fi
done
