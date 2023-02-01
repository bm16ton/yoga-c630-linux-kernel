cmd_drivers/input/touchscreen/elo.mod := printf '%s\n'   elo.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/elo.mod
