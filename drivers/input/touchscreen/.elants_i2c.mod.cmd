cmd_drivers/input/touchscreen/elants_i2c.mod := printf '%s\n'   elants_i2c.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/elants_i2c.mod
