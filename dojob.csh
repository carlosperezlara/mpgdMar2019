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

root -b -l -q resolution.C\($1,1\) #D1
#root -b -l -q resolution.C\($1,2\) #D2
#root -b -l -q resolution.C\($1,3\) #D3
#root -b -l -q resolution.C\($1,4\) #D4
#root -b -l -q resolution.C\($1,5\) #D5
#root -b -l -q resolution.C\($1,6\) #D6
#root -b -l -q resolution.C\($1,7\) #D7
#root -b -l -q resolution.C\($1,8\) #D8
#root -b -l -q track.C\($1\)


#mv resolution_*${A}.pdf res/
