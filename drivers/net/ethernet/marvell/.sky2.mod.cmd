cmd_drivers/net/ethernet/marvell/sky2.mod := printf '%s\n'   sky2.o | awk '!x[$$0]++ { print("drivers/net/ethernet/marvell/"$$0) }' > drivers/net/ethernet/marvell/sky2.mod
