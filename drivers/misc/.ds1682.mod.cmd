cmd_drivers/misc/ds1682.mod := printf '%s\n'   ds1682.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/ds1682.mod
