cmd_drivers/net/ethernet/amd/pcnet32.mod := printf '%s\n'   pcnet32.o | awk '!x[$$0]++ { print("drivers/net/ethernet/amd/"$$0) }' > drivers/net/ethernet/amd/pcnet32.mod
