cmd_drivers/media/rc/ttusbir.mod := printf '%s\n'   ttusbir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ttusbir.mod
