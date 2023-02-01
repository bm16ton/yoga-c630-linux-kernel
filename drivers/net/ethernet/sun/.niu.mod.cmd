cmd_drivers/net/ethernet/sun/niu.mod := printf '%s\n'   niu.o | awk '!x[$$0]++ { print("drivers/net/ethernet/sun/"$$0) }' > drivers/net/ethernet/sun/niu.mod
