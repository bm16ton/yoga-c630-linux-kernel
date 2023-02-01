cmd_drivers/net/ethernet/adaptec/starfire.mod := printf '%s\n'   starfire.o | awk '!x[$$0]++ { print("drivers/net/ethernet/adaptec/"$$0) }' > drivers/net/ethernet/adaptec/starfire.mod
