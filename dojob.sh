#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N runs.dat.good | tail -1`
echo $A

root -b analysis2019.C\($A\)
mv fnal-0$A.root rootfiles/
root -b plot2019.C\($A\)
mv quicklook_$A.pdf quicklook/
