cmd_drivers/net/mdio/mdio-thunder.mod := printf '%s\n'   mdio-thunder.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-thunder.mod
