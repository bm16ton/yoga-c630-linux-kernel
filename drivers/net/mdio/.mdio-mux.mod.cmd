cmd_drivers/net/mdio/mdio-mux.mod := printf '%s\n'   mdio-mux.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-mux.mod
