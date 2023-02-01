cmd_drivers/net/ethernet/natsemi/natsemi.mod := printf '%s\n'   natsemi.o | awk '!x[$$0]++ { print("drivers/net/ethernet/natsemi/"$$0) }' > drivers/net/ethernet/natsemi/natsemi.mod
