cmd_drivers/net/ethernet/dec/tulip/uli526x.mod := printf '%s\n'   uli526x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dec/tulip/"$$0) }' > drivers/net/ethernet/dec/tulip/uli526x.mod
