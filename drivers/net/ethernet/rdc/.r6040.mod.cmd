cmd_drivers/net/ethernet/rdc/r6040.mod := printf '%s\n'   r6040.o | awk '!x[$$0]++ { print("drivers/net/ethernet/rdc/"$$0) }' > drivers/net/ethernet/rdc/r6040.mod
