cmd_drivers/net/phy/marvell10g.mod := printf '%s\n'   marvell10g.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/marvell10g.mod
