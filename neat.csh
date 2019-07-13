#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N elog/runs.dat.good | tail -1`
echo $A

root -b -l -q organizeData.C\($1,1\) #D1
