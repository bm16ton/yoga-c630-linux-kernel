cmd_drivers/net/phy/ste10Xp.mod := printf '%s\n'   ste10Xp.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/ste10Xp.mod
