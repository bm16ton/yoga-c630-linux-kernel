cmd_drivers/input/touchscreen/gunze.mod := printf '%s\n'   gunze.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/gunze.mod
