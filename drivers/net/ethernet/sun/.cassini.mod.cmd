cmd_drivers/net/ethernet/sun/cassini.mod := printf '%s\n'   cassini.o | awk '!x[$$0]++ { print("drivers/net/ethernet/sun/"$$0) }' > drivers/net/ethernet/sun/cassini.mod
