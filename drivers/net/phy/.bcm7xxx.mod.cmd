cmd_drivers/net/phy/bcm7xxx.mod := printf '%s\n'   bcm7xxx.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/bcm7xxx.mod
