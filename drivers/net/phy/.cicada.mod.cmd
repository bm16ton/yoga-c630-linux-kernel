cmd_drivers/net/phy/cicada.mod := printf '%s\n'   cicada.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/cicada.mod
