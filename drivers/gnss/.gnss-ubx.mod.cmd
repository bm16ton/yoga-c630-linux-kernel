cmd_drivers/gnss/gnss-ubx.mod := printf '%s\n'   ubx.o | awk '!x[$$0]++ { print("drivers/gnss/"$$0) }' > drivers/gnss/gnss-ubx.mod
