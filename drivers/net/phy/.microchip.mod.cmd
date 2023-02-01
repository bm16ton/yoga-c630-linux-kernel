cmd_drivers/net/phy/microchip.mod := printf '%s\n'   microchip.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/microchip.mod
