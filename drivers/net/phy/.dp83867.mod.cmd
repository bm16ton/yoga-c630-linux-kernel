cmd_drivers/net/phy/dp83867.mod := printf '%s\n'   dp83867.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/dp83867.mod
