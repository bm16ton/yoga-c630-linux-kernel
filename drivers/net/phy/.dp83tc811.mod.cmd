cmd_drivers/net/phy/dp83tc811.mod := printf '%s\n'   dp83tc811.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/dp83tc811.mod
