cmd_drivers/net/nlmon.mod := printf '%s\n'   nlmon.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/nlmon.mod
