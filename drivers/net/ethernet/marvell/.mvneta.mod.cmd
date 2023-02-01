cmd_drivers/net/ethernet/marvell/mvneta.mod := printf '%s\n'   mvneta.o | awk '!x[$$0]++ { print("drivers/net/ethernet/marvell/"$$0) }' > drivers/net/ethernet/marvell/mvneta.mod
