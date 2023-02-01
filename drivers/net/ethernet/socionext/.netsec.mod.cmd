cmd_drivers/net/ethernet/socionext/netsec.mod := printf '%s\n'   netsec.o | awk '!x[$$0]++ { print("drivers/net/ethernet/socionext/"$$0) }' > drivers/net/ethernet/socionext/netsec.mod
