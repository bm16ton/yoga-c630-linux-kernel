cmd_drivers/auxdisplay/charlcd.mod := printf '%s\n'   charlcd.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/charlcd.mod
