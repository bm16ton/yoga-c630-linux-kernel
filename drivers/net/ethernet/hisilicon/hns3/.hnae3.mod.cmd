cmd_drivers/net/ethernet/hisilicon/hns3/hnae3.mod := printf '%s\n'   hnae3.o | awk '!x[$$0]++ { print("drivers/net/ethernet/hisilicon/hns3/"$$0) }' > drivers/net/ethernet/hisilicon/hns3/hnae3.mod
