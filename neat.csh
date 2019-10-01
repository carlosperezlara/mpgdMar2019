#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N elog/runs.dat.good | tail -1`
echo $A

root -b -l -q organizeData.C\($1,1\) #D1
root -b -l -q organizeData.C\($1,2\) #D1
root -b -l -q organizeData.C\($1,3\) #D1
root -b -l -q organizeData.C\($1,4\) #D1
root -b -l -q organizeData.C\($1,5\) #D1
root -b -l -q organizeData.C\($1,6\) #D1
root -b -l -q organizeData.C\($1,7\) #D1
root -b -l -q organizeData.C\($1,8\) #D1
