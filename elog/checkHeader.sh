rm instMar26.runs.ext
for X in `awk {'print $1'} instMar26.runs`
do
    ddump -t9 -p906 ~/T1429/2019-03/MissionControl/DATA/beam/beam-0000$X-0000.evt | awk '{print $1}' >> instMar26.runs.ext
done
