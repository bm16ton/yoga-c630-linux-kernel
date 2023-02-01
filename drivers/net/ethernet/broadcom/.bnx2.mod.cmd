cmd_drivers/net/ethernet/broadcom/bnx2.mod := printf '%s\n'   bnx2.o | awk '!x[$$0]++ { print("drivers/net/ethernet/broadcom/"$$0) }' > drivers/net/ethernet/broadcom/bnx2.mod
