for X in 1 2 3 4 5 6 7 8
do
    rm D${X}.txt
    #head -$X configall.txt | tail -1 > D$X.txt.start
    #ln -s D${X}.txt.start D${X}.txt
    #cp ../D${X}.beamnew .
    #ln -s D${X}.beamnew D${X}.txt
    ln -s D${X}.beamnew_off D${X}.txt
done
