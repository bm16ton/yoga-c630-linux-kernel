cmd_drivers/net/ethernet/jme.mod := printf '%s\n'   jme.o | awk '!x[$$0]++ { print("drivers/net/ethernet/"$$0) }' > drivers/net/ethernet/jme.mod
