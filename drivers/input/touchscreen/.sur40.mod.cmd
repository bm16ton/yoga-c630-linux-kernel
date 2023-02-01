cmd_drivers/input/touchscreen/sur40.mod := printf '%s\n'   sur40.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/sur40.mod
