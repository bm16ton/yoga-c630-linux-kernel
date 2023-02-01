cmd_drivers/input/touchscreen/tps6507x-ts.mod := printf '%s\n'   tps6507x-ts.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/tps6507x-ts.mod
