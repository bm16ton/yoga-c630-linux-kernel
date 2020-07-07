#!/bin/bash
for i in $(seq 0 20) ; do
TYPE=$(cat /sys/class/hwmon/hwmon$i/name)
TEMP=$(cat /sys/class/hwmon/hwmon$i/temp1_input)
FTEMP=$(echo "$TEMP / 1000" |bc)
FTEMP2=$(echo "scale=2;((9/5) * $FTEMP) + 32" |bc)
echo "$TYPE = $FTEMP"C" $FTEMP2"F""
done
cat /sys/class/hwmon/hwmon21/name
cat /sys/class/hwmon/hwmon21/temp1_label
cat /sys/class/hwmon/hwmon21/temp2_label
cat /sys/class/hwmon/hwmon22/name
cat /sys/class/hwmon/hwmon22/temp1_label
cat /sys/class/hwmon/hwmon22/temp2_label
cat /sys/class/hwmon/hwmon23/name
cat /sys/class/hwmon/hwmon23/temp1_label
cat /sys/class/hwmon/hwmon23/temp2_label
exit
