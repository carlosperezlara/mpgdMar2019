for X in 1 2 3 4 5 6 7 8
do
    rm D${X}.txt
    #head -$X configall.txt | tail -1 > D$X.txt.start
    #ln -s D${X}.txt.start D${X}.txt
    #cp ../D${X}.beamnew .
    #ln -s D${X}.beamnew D${X}.txt
    #ln -s D${X}.beamnew_off2 D${X}.txt
    #ln -s D${X}.beamnew_off3 D${X}.txt
    #ln -s D${X}_Static.txt D${X}.txt
    #ln -s D${X}_Static4.txt D${X}.txt
    ln -s D${X}_Static4.dep D${X}.txt

    rm fiducial.D${X}.dat
    ln -s fiducial.D${X}.dat.manual fiducial.D${X}.dat 
done
