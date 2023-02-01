cmd_drivers/net/phy/bcm-phy-lib.mod := printf '%s\n'   bcm-phy-lib.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/bcm-phy-lib.mod
