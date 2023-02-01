cmd_drivers/net/ethernet/silan/sc92031.mod := printf '%s\n'   sc92031.o | awk '!x[$$0]++ { print("drivers/net/ethernet/silan/"$$0) }' > drivers/net/ethernet/silan/sc92031.mod
