cmd_drivers/net/dsa/mv88e6060.mod := printf '%s\n'   mv88e6060.o | awk '!x[$$0]++ { print("drivers/net/dsa/"$$0) }' > drivers/net/dsa/mv88e6060.mod
