cmd_drivers/net/ethernet/ti/tlan.mod := printf '%s\n'   tlan.o | awk '!x[$$0]++ { print("drivers/net/ethernet/ti/"$$0) }' > drivers/net/ethernet/ti/tlan.mod
