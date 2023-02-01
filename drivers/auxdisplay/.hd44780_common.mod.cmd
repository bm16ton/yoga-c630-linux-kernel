cmd_drivers/auxdisplay/hd44780_common.mod := printf '%s\n'   hd44780_common.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/hd44780_common.mod
