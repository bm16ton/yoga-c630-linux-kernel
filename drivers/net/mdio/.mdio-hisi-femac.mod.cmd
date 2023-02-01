cmd_drivers/net/mdio/mdio-hisi-femac.mod := printf '%s\n'   mdio-hisi-femac.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-hisi-femac.mod
