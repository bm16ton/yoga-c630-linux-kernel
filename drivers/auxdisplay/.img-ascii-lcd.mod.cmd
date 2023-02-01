cmd_drivers/auxdisplay/img-ascii-lcd.mod := printf '%s\n'   img-ascii-lcd.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/img-ascii-lcd.mod
