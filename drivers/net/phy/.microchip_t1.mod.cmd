cmd_drivers/net/phy/microchip_t1.mod := printf '%s\n'   microchip_t1.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/microchip_t1.mod
