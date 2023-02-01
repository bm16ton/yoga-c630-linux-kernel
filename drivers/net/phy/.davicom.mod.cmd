cmd_drivers/net/phy/davicom.mod := printf '%s\n'   davicom.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/davicom.mod
