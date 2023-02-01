cmd_drivers/media/rc/imon.mod := printf '%s\n'   imon.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/imon.mod
