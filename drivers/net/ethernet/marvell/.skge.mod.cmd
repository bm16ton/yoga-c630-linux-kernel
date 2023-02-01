cmd_drivers/net/ethernet/marvell/skge.mod := printf '%s\n'   skge.o | awk '!x[$$0]++ { print("drivers/net/ethernet/marvell/"$$0) }' > drivers/net/ethernet/marvell/skge.mod
