cmd_drivers/net/phy/micrel.mod := printf '%s\n'   micrel.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/micrel.mod
