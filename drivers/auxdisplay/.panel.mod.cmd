cmd_drivers/auxdisplay/panel.mod := printf '%s\n'   panel.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/panel.mod
