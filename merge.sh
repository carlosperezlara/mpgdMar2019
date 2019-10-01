#!/bin/bash

XXXXGEM_B00e_D8_I0.txt4    GEM_V00a_D1_I6.txt4    MM_Z03k.A_D2_I4.txt4   MM_Z03k.B_D7_I0.txt4
XXXXGEM_B00e_D8_I1.txt4    GEM_Z03k.A_D4_I5.txt4  MM_Z03k.A_D2_I5.txt4   MM_Z03k.B_D7_I1.txt4
XXXXGEM_B01a_D5_I0.txt4    GEM_Z03k.A_D4_I6.txt4  MM_Z03k.A_D2_I6.txt4   MM_Z03k.B_D7_I2.txt4
XXXXGEM_B01a_D5_I1.txt4    GEM_Z03k.A_D8_I2.txt4  MM_Z03k.A_D4_I0.txt4   uRW_B00e_D3_I3.txt4
XXXXGEM_B01a_D5_I2.txt4    GEM_Z03k.A_D8_I3.txt4  MM_Z03k.A_D4_I1.txt4   XXXXuRW_B01a_D3_I0.txt4
GEM_B01a_D5_I3.txt4    GEM_Z03k.A_D8_I4.txt4  MM_Z03k.A_D4_I2.txt4   XXXXuRW_B01a_D3_I1.txt4
XXXXGEM_B01a_D5_I4.txt4    GEM_Z03k.D_D5_I3.txt4  MM_Z03k.A_D4_I3.txt4   XXXXuRW_B01a_D3_I2.txt4
GEM_V00a_D1_I0.txt4    MM_B01a_D7_I3.txt4     MM_Z03k.A_D4_I4.txt4   uRW_B01a_D3_I4.txt4
GEM_V00a_D1_I1.txt4    MM_B01a_D7_I4.txt4     MM_Z03k.A_D6_I0.txt4   uRW_B01a_D3_I5.txt4
GEM_V00a_D1_I2.txt4    MM_Z03k.A_D2_I0.txt4   MM_Z03k.A_D6_I1.txt4   uRW_B01a_D3_I6.txt4
GEM_V00a_D1_I3.txt4    MM_Z03k.A_D2_I1.txt4   MM_Z03k.A_D6_I2.txt4
GEM_V00a_D1_I4.txt4    MM_Z03k.A_D2_I2.txt4   MM_Z03k.A_D6_I3.txt4
GEM_V00a_D1_I5.txt4    MM_Z03k.A_D2_I3.txt4   MM_Z03k.A_D6_I4.txt4


######
cat GEM_B00e_D8_I0.txt4 GEM_B00e_D8_I1.txt4 > GEM_B00e_INST01.txt
######
cat uRW_B01a_D3_I0.txt uRW_B01a_D3_I1.txt uRW_B01a_D3_I2.txt > uRW_B01a_INST02.txt
######
cat GEM_B01a_D5_I4.txt4 > GEM_B01a_INST4.txt
######
cat MM_B01a_D7_I3.txt MM_B01a_D7_I4.txt > MM_B01a_INST34.txt
######
cat GEM_V00a_D1_I4.txt GEM_V00a_D1_I5.txt GEM_V00a_D1_I6.txt > GEM_V00a_INST46.txt



cat GEM_Z03k.A_INST2.txt GEM_Z03k.A_INST3.txt > GEM_Z03k.A_INST23.txt
#GEM_Z03k.A_INST4.txt
cat GEM_Z03k.A_INST5.txt GEM_Z03k.A_INST6.txt > GEM_Z03k.A_INST56.txt
#GEM_Z03k.D_INST3.txt
#MM_B01a_INST2.txt
cat MM_Z03k.A_INST1.2.txt MM_Z03k.A_INST2.2.txt MM_Z03k.A_INST3.2.txt MM_Z03k.A_INST4.2.txt MM_Z03k.A_INST5.2.txt MM_Z03k.A_INST6.2.txt > MM_Z03k.A_INST16.2.txt
cat MM_Z03k.A_INST0.4.txt MM_Z03k.A_INST1.4.txt MM_Z03k.A_INST2.4.txt > MM_Z03k.A_INST02.4.txt
cat MM_Z03k.A_INST3.4.txt MM_Z03k.A_INST4.4.txt > MM_Z03k.A_INST34.4.txt
cat MM_Z03k.A_INST0.6.txt MM_Z03k.A_INST1.6.txt MM_Z03k.A_INST2.6.txt MM_Z03k.A_INST3.6.txt MM_Z03k.A_INST4.6.txt > MM_Z03k.A_INST04.6.txt
#MM_Z03k.A_INST5.txt
#MM_Z03k.A_INST6.txt
cat MM_Z03k.B_INST0.txt MM_Z03k.B_INST1.txt MM_Z03k.B_INST2.txt > MM_Z03k.B_INST02.txt
#uRW_B00e_INST2.txt
#uRW_B00e_INST3.txt
