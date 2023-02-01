cmd_drivers/net/ethernet/sis/sis190.mod := printf '%s\n'   sis190.o | awk '!x[$$0]++ { print("drivers/net/ethernet/sis/"$$0) }' > drivers/net/ethernet/sis/sis190.mod
