cmd_drivers/net/mdio/mdio-cavium.mod := printf '%s\n'   mdio-cavium.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-cavium.mod
