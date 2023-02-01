cmd_drivers/input/touchscreen/ad7879.mod := printf '%s\n'   ad7879.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/ad7879.mod
