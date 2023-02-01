cmd_drivers/mfd/simple-mfd-i2c.mod := printf '%s\n'   simple-mfd-i2c.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/simple-mfd-i2c.mod
