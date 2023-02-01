cmd_drivers/net/ethernet/via/via-velocity.mod := printf '%s\n'   via-velocity.o | awk '!x[$$0]++ { print("drivers/net/ethernet/via/"$$0) }' > drivers/net/ethernet/via/via-velocity.mod
