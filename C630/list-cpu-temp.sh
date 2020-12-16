#!/bin/bash
for i in $(seq 0 10) ; do
TYPE=$(cat /sys/class/thermal/thermal_zone$i/type)
TEMP=$(cat /sys/class/thermal/thermal_zone$i/temp)
FTEMP=$(echo "$TEMP / 1000" |bc)
FTEMP2=$(echo "scale=2;((9/5) * $FTEMP) + 32" |bc)
echo "$TYPE = $FTEMP"C" $FTEMP2"F""
done 
