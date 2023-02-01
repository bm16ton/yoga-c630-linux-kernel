cmd_drivers/media/rc/streamzap.mod := printf '%s\n'   streamzap.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/streamzap.mod
