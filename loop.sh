for X in `awk '{print $1}' elog/instMar26.det`
do
    root -b analysis2019.C\($X\)
    mv fnal-0$X.root rootfiles/
done
