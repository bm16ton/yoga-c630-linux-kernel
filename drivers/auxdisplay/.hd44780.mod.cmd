cmd_drivers/auxdisplay/hd44780.mod := printf '%s\n'   hd44780.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/hd44780.mod
