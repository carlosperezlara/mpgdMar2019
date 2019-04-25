for X in 1 2 3 4 5 6 7 8
do
    head -$X configall.txt | tail -1 > D$X.txt
done
