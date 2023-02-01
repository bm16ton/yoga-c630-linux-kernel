cmd_drivers/net/phy/bcm87xx.mod := printf '%s\n'   bcm87xx.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/bcm87xx.mod
