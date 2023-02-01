cmd_drivers/net/ethernet/marvell/mvmdio.mod := printf '%s\n'   mvmdio.o | awk '!x[$$0]++ { print("drivers/net/ethernet/marvell/"$$0) }' > drivers/net/ethernet/marvell/mvmdio.mod
