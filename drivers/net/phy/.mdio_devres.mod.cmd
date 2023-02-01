cmd_drivers/net/phy/mdio_devres.mod := printf '%s\n'   mdio_devres.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/mdio_devres.mod
