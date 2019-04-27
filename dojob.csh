#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N elog/runs.dat.good | tail -1`
echo $A

#root -b -l -q analysis2019.C\($A\)
#mv fnal-0$A.root rootfiles/
#root -b -l -q plot2019.C\($A\)
#mv quicklook_$A.pdf quicklook/
#root -b -l -q plot2019_extracut.C\($A\)
#mv quicklook_${A}_extracut.pdf quicklook/

root -b -l -q resolution.C\($1\)
mv resolution_*${A}.pdf res/
