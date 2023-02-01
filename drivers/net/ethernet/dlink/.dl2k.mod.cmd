cmd_drivers/net/ethernet/dlink/dl2k.mod := printf '%s\n'   dl2k.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dlink/"$$0) }' > drivers/net/ethernet/dlink/dl2k.mod
