cmd_drivers/net/ethernet/atheros/atlx/atl1.mod := printf '%s\n'   atl1.o | awk '!x[$$0]++ { print("drivers/net/ethernet/atheros/atlx/"$$0) }' > drivers/net/ethernet/atheros/atlx/atl1.mod
