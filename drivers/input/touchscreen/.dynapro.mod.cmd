cmd_drivers/input/touchscreen/dynapro.mod := printf '%s\n'   dynapro.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/dynapro.mod
