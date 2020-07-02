for f in /sys/class/thermal/thermal_zone* ; do
    TYPE=`cat $f/type`
    TEMP=`cat $f/temp`
    FTEMP=$(echo "$TEMP / 1000" |bc)
    FTEMP2=$(echo "scale=2;((9/5) * $FTEMP) + 32" |bc)
echo "$TYPE = $FTEMP"C" $FTEMP2"F""
done

