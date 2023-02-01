cmd_drivers/net/can/sja1000/sja1000.mod := printf '%s\n'   sja1000.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/sja1000.mod
