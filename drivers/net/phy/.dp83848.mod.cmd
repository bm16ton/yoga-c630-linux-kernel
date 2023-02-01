cmd_drivers/net/phy/dp83848.mod := printf '%s\n'   dp83848.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/dp83848.mod
