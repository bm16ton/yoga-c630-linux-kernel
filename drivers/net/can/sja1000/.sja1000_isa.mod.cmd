cmd_drivers/net/can/sja1000/sja1000_isa.mod := printf '%s\n'   sja1000_isa.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/sja1000_isa.mod
