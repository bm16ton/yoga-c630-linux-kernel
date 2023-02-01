cmd_drivers/net/phy/broadcom.mod := printf '%s\n'   broadcom.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/broadcom.mod
