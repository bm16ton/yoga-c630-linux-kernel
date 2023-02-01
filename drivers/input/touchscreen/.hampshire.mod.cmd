cmd_drivers/input/touchscreen/hampshire.mod := printf '%s\n'   hampshire.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/hampshire.mod
