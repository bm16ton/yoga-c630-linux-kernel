cmd_drivers/net/ethernet/hisilicon/hisi_femac.mod := printf '%s\n'   hisi_femac.o | awk '!x[$$0]++ { print("drivers/net/ethernet/hisilicon/"$$0) }' > drivers/net/ethernet/hisilicon/hisi_femac.mod
