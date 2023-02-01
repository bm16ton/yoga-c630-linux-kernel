cmd_drivers/net/ethernet/hisilicon/hns_mdio.mod := printf '%s\n'   hns_mdio.o | awk '!x[$$0]++ { print("drivers/net/ethernet/hisilicon/"$$0) }' > drivers/net/ethernet/hisilicon/hns_mdio.mod
