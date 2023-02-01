cmd_drivers/auxdisplay/lcd2s.mod := printf '%s\n'   lcd2s.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/lcd2s.mod
