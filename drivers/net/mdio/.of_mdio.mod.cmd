cmd_drivers/net/mdio/of_mdio.mod := printf '%s\n'   of_mdio.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/of_mdio.mod
