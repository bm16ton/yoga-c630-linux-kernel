cmd_drivers/auxdisplay/line-display.mod := printf '%s\n'   line-display.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/line-display.mod
