cmd_drivers/input/touchscreen/touchright.mod := printf '%s\n'   touchright.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/touchright.mod
