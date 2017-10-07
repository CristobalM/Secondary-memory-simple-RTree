#!/bin/bash
for exp in {1..3}
do
    expoutput="output_experiment_$exp"
    time ./logaritmos_tarea1 > ${expoutput}
    #echo ${expoutput}
done
