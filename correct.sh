#!/bin/bash

for X in GEM_B00e_INST0.txt     GEM_V00a_INST4.txt     MM_B01a_INST3.txt      MM_Z03k.B_INST1.txt   GEM_B00e_INST1.txt     GEM_V00a_INST5.txt     MM_B01a_INST4.txt      MM_Z03k.B_INST2.txt GEM_B01a_INST0.txt     GEM_V00a_INST6.txt     MM_Z03k.A_INST0.txt    uRW_B00e_INST2.txt GEM_Z03k.A_INST2.txt   uRW_B00e_INST3.txt     GEM_B01a_INST1.txt     MM_Z03k.A_INST1.txt uRW_B01a_INST0.txt     GEM_B01a_INST2.txt     GEM_Z03k.A_INST3.txt   MM_Z03k.A_INST2.txt GEM_B01a_INST4.txt     GEM_Z03k.A_INST4.txt   MM_Z03k.A_INST3.txt    uRW_B01a_INST1.txt GEM_V00a_INST0.txt     GEM_Z03k.A_INST5.txt   uRW_B01a_INST2.txt     MM_Z03k.A_INST4.txt uRW_B01a_INST4.txt     GEM_V00a_INST1.txt     GEM_Z03k.A_INST6.txt   MM_Z03k.A_INST5.txt GEM_V00a_INST2.txt     GEM_Z03k.D_INST3.txt   MM_Z03k.A_INST6.txt    uRW_B01a_INST5.txt GEM_V00a_INST3.txt     MM_B01a_INST2.txt      MM_Z03k.B_INST0.txt    uRW_B01a_INST6.txt
do
    sed 's/inf/9999/g' $X > tmp.txt
    mv tmp.txt $X
done

