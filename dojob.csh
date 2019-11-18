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

foreach det (1 2 3 4 5 6 7 8)
#    root -b -l -q resolution2.C\($1,$det\) #D1
end
root -b -l -q fullchambercorrelation.C\($1\)

#root -b -l -q track.C\($1\)
