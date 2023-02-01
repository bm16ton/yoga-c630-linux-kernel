cmd_drivers/net/ethernet/hisilicon/hns/hnae.mod := printf '%s\n'   hnae.o | awk '!x[$$0]++ { print("drivers/net/ethernet/hisilicon/hns/"$$0) }' > drivers/net/ethernet/hisilicon/hns/hnae.mod
