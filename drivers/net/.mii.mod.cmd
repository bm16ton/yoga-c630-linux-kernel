cmd_drivers/net/mii.mod := printf '%s\n'   mii.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/mii.mod
