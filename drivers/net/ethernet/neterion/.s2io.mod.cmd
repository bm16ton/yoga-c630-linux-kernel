cmd_drivers/net/ethernet/neterion/s2io.mod := printf '%s\n'   s2io.o | awk '!x[$$0]++ { print("drivers/net/ethernet/neterion/"$$0) }' > drivers/net/ethernet/neterion/s2io.mod
