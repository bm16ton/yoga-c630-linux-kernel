cmd_drivers/net/phy/bcm54140.mod := printf '%s\n'   bcm54140.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/bcm54140.mod
