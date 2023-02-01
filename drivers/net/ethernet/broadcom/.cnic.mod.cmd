cmd_drivers/net/ethernet/broadcom/cnic.mod := printf '%s\n'   cnic.o | awk '!x[$$0]++ { print("drivers/net/ethernet/broadcom/"$$0) }' > drivers/net/ethernet/broadcom/cnic.mod
