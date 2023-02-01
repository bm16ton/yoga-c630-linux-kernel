cmd_drivers/net/phy/phylink.mod := printf '%s\n'   phylink.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/phylink.mod
