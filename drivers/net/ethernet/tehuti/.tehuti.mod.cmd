cmd_drivers/net/ethernet/tehuti/tehuti.mod := printf '%s\n'   tehuti.o | awk '!x[$$0]++ { print("drivers/net/ethernet/tehuti/"$$0) }' > drivers/net/ethernet/tehuti/tehuti.mod
