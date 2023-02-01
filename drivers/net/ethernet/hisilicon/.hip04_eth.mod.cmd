cmd_drivers/net/ethernet/hisilicon/hip04_eth.mod := printf '%s\n'   hip04_eth.o | awk '!x[$$0]++ { print("drivers/net/ethernet/hisilicon/"$$0) }' > drivers/net/ethernet/hisilicon/hip04_eth.mod
