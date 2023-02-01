cmd_drivers/net/phy/sfp.mod := printf '%s\n'   sfp.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/sfp.mod
