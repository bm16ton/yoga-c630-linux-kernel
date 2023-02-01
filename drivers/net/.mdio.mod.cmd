cmd_drivers/net/mdio.mod := printf '%s\n'   mdio.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/mdio.mod
