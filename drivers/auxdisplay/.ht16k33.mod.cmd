cmd_drivers/auxdisplay/ht16k33.mod := printf '%s\n'   ht16k33.o | awk '!x[$$0]++ { print("drivers/auxdisplay/"$$0) }' > drivers/auxdisplay/ht16k33.mod
