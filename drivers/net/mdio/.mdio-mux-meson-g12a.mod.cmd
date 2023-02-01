cmd_drivers/net/mdio/mdio-mux-meson-g12a.mod := printf '%s\n'   mdio-mux-meson-g12a.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/mdio-mux-meson-g12a.mod
