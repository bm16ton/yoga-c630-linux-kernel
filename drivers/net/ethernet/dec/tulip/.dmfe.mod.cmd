cmd_drivers/net/ethernet/dec/tulip/dmfe.mod := printf '%s\n'   dmfe.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dec/tulip/"$$0) }' > drivers/net/ethernet/dec/tulip/dmfe.mod
