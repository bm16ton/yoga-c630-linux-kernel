cmd_drivers/input/touchscreen/tsc2007.mod := printf '%s\n'   tsc2007_core.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/tsc2007.mod
