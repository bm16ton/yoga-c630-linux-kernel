cmd_drivers/net/phy/uPD60620.mod := printf '%s\n'   uPD60620.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/uPD60620.mod
