cmd_drivers/net/phy/amd.mod := printf '%s\n'   amd.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/amd.mod
