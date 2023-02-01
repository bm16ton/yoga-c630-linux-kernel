cmd_drivers/net/mdio/fwnode_mdio.mod := printf '%s\n'   fwnode_mdio.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/fwnode_mdio.mod
