cmd_drivers/net/ethernet/8390/8390.mod := printf '%s\n'   8390.o | awk '!x[$$0]++ { print("drivers/net/ethernet/8390/"$$0) }' > drivers/net/ethernet/8390/8390.mod
