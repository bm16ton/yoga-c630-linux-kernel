cmd_drivers/net/phy/marvell.mod := printf '%s\n'   marvell.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/marvell.mod
