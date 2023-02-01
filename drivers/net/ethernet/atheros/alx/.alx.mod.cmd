cmd_drivers/net/ethernet/atheros/alx/alx.mod := printf '%s\n'   main.o ethtool.o hw.o | awk '!x[$$0]++ { print("drivers/net/ethernet/atheros/alx/"$$0) }' > drivers/net/ethernet/atheros/alx/alx.mod
