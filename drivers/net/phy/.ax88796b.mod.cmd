cmd_drivers/net/phy/ax88796b.mod := printf '%s\n'   ax88796b.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/ax88796b.mod
