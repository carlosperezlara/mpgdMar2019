#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N elog/runs.dat.good | tail -1`
echo $A

foreach win (1 3 5 7)
#foreach win (8)
    root -b -l -q analysis2019.C\($A,-1,${win},2\)
    mv fnal-0$A.root test/fnal-0$A-${win}.root
end


#root -b -l -q plot2019.C\($A\)
#mv quicklook_$A.pdf quicklook/
#root -b -l -q plot2019_extracut.C\($A\)
#mv quicklook_${A}_extracut.pdf quicklook/

#foreach det (1 2 3 4 5 6 7 8)
#foreach det (4)
#    rm res/D$det/data/reso_*run$A.dat
#    rm res/D$det/*$A.pdf
#    rm res/D$det/*$A.png
#    root -b -l -q resolution2.C\($1,$det\) #D1
#end
#root -b -l -q fullchambercorrelation.C\($1\)

#root -b -l -q track.C\($1\)

