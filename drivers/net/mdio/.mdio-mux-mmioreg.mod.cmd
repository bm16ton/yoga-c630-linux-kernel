cmd_drivers/net/mdio/mdio-mux-mmioreg.mod := printf '%s\n'   mdio-mux-mmioreg.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-mux-mmioreg.mod
