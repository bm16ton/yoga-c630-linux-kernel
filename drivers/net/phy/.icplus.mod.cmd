cmd_drivers/net/phy/icplus.mod := printf '%s\n'   icplus.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/icplus.mod
