cmd_drivers/net/mdio/mdio-i2c.mod := printf '%s\n'   mdio-i2c.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-i2c.mod
