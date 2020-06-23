#!/bin/bash
for i in $(seq 0 9) ; do
TYPE=$(cat /sys/class/thermal/thermal_zone$i/type)
TEMP=$(cat /sys/class/thermal/thermal_zone$i/temp)
echo "$TYPE = $TEMP"
done 
