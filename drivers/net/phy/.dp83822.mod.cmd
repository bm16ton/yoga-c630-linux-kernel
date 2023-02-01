cmd_drivers/net/phy/dp83822.mod := printf '%s\n'   dp83822.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/dp83822.mod
