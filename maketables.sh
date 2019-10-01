#!/bin/bash

for X in `cat list`
do
    root -b -q maketable.C\(\"${X}\"\)
done

#root -b -q maketable.C\(\"GEM_B00e_INST01\"\)
#root -b -q maketable.C\(\"GEM_B01a_INST02\"\)
#root -b -q maketable.C\(\"GEM_B01a_INST4\"\)
#root -b -q maketable.C\(\"GEM_V00a_INST02\"\)
#root -b -q maketable.C\(\"GEM_V00a_INST3\"\)
#root -b -q maketable.C\(\"GEM_V00a_INST46\"\)
#root -b -q maketable.C\(\"GEM_Z03k.A_INST23\"\)
#GEM_Z03k.A_INST4.txt
#root -b -q maketable.C\(\"GEM_Z03k.A_INST56\"\)
#root -b -q maketable.C\(\"GEM_Z03k.D_INST3\"\)
#MM_B01a_INST2.txt
#root -b -q maketable.C\(\"MM_B01a_INST34\"\)

#root -b -q maketable.C\(\"MM_Z03k.A_INST0.2\"\)
#root -b -q maketable.C\(\"MM_Z03k.A_INST02.4\"\)
#root -b -q maketable.C\(\"MM_Z03k.A_INST04.6\"\)
#root -b -q maketable.C\(\"MM_Z03k.A_INST16.2\"\)
#root -b -q maketable.C\(\"MM_Z03k.A_INST34.4\"\)
#root -b -q maketable.C\(\"MM_Z03k.A_INST7.2\"\)

#MM_Z03k.A_INST5.txt
#MM_Z03k.A_INST6.txt
#root -b -q maketable.C\(\"MM_Z03k.B_INST02\"\)
#uRW_B00e_INST2.txt
#root -b -q maketable.C\(\"uRW_B00e_INST3\"\)
#root -b -q maketable.C\(\"uRW_B01a_INST02\"\)
#root -b -q maketable.C\(\"uRW_B01a_INST46\"\)
