cmd_drivers/net/mdio/mdio-bcm-unimac.mod := printf '%s\n'   mdio-bcm-unimac.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-bcm-unimac.mod
