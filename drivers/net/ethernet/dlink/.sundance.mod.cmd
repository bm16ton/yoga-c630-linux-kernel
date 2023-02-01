cmd_drivers/net/ethernet/dlink/sundance.mod := printf '%s\n'   sundance.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dlink/"$$0) }' > drivers/net/ethernet/dlink/sundance.mod
