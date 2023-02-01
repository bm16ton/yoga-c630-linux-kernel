cmd_drivers/input/touchscreen/ad7877.mod := printf '%s\n'   ad7877.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/ad7877.mod
