cmd_drivers/net/ethernet/atheros/atlx/atl2.mod := printf '%s\n'   atl2.o | awk '!x[$$0]++ { print("drivers/net/ethernet/atheros/atlx/"$$0) }' > drivers/net/ethernet/atheros/atlx/atl2.mod
