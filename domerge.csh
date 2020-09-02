#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N elog/runs.dat.good | tail -1`
echo $A

#root -b -l -q analysis2019.C\($A,-1,-1,-1,2\)
#mv fnal-0$A.root rootfilesmerge/fnal-0$A-merge2.root
#root -b -l -q analysis2019.C\($A,-1,-1,-1,3\)
#mv fnal-0$A.root rootfilesmerge/fnal-0$A-merge3.root
#root -b -l -q analysis2019.C\($A,-1,-1,-1,4\)
#mv fnal-0$A.root rootfilesmerge/fnal-0$A-merge4.root
#root -b -l -q analysis2019.C\($A,-1,-1,-1,5\)
#mv fnal-0$A.root rootfilesmerge/fnal-0$A-merge5.root

foreach rebin (1 2 3 4 5)
#foreach rebin (1 2)
    #root -b -l -q analysis2019.C\($A,-1,-1,-1,$rebin\)
    #mv fnal-0$A.root rootfilesmerge/fnal-0$A-merge$rebin.root
    foreach det (5)
	root -b -l -q resolution2_GX_merge.C\($1,$det,0.90,0.80,$rebin\) #D1
    end
end

