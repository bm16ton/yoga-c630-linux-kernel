cmd_drivers/net/ethernet/fealnx.mod := printf '%s\n'   fealnx.o | awk '!x[$$0]++ { print("drivers/net/ethernet/"$$0) }' > drivers/net/ethernet/fealnx.mod
