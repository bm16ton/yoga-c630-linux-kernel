cmd_drivers/net/ethernet/3com/3c59x.mod := printf '%s\n'   3c59x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/3com/"$$0) }' > drivers/net/ethernet/3com/3c59x.mod
