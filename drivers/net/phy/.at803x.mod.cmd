cmd_drivers/net/phy/at803x.mod := printf '%s\n'   at803x.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/at803x.mod
