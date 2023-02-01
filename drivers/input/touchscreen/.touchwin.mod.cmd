cmd_drivers/input/touchscreen/touchwin.mod := printf '%s\n'   touchwin.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/touchwin.mod
