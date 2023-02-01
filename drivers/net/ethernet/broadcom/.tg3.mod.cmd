cmd_drivers/net/ethernet/broadcom/tg3.mod := printf '%s\n'   tg3.o | awk '!x[$$0]++ { print("drivers/net/ethernet/broadcom/"$$0) }' > drivers/net/ethernet/broadcom/tg3.mod
