cmd_drivers/net/phy/et1011c.mod := printf '%s\n'   et1011c.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/et1011c.mod
