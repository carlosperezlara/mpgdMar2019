#!/bin/bash

for X in `cat list.mer`
do
    root -b -q makeplots.C\(\"${X}\"\)
done
