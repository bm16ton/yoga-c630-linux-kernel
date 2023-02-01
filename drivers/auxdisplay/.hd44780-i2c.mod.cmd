cmd_drivers/auxdisplay/hd44780-i2c.mod := printf '%s\n'   hd44780i2c.o hd44780i2c-dev.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/hd44780-i2c.mod
