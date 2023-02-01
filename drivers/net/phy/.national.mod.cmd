cmd_drivers/net/phy/national.mod := printf '%s\n'   national.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/national.mod
