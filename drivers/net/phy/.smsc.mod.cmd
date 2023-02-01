cmd_drivers/net/phy/smsc.mod := printf '%s\n'   smsc.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/smsc.mod
