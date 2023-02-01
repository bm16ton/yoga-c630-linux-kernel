cmd_drivers/input/touchscreen/usbtouchscreen.mod := printf '%s\n'   usbtouchscreen.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/usbtouchscreen.mod
