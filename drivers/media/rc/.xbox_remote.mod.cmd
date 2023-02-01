cmd_drivers/media/rc/xbox_remote.mod := printf '%s\n'   xbox_remote.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/xbox_remote.mod
