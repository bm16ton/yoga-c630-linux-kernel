cmd_drivers/net/phy/lxt.mod := printf '%s\n'   lxt.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/lxt.mod
