cmd_drivers/net/phy/fixed_phy.mod := printf '%s\n'   fixed_phy.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/fixed_phy.mod
