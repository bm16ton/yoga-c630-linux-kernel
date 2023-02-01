cmd_drivers/media/rc/imon_raw.mod := printf '%s\n'   imon_raw.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/imon_raw.mod
