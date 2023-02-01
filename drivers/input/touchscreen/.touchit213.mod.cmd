cmd_drivers/input/touchscreen/touchit213.mod := printf '%s\n'   touchit213.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/touchit213.mod
