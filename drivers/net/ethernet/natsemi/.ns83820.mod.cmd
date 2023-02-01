cmd_drivers/net/ethernet/natsemi/ns83820.mod := printf '%s\n'   ns83820.o | awk '!x[$$0]++ { print("drivers/net/ethernet/natsemi/"$$0) }' > drivers/net/ethernet/natsemi/ns83820.mod
