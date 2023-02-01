cmd_drivers/net/can/cc770/cc770.mod := printf '%s\n'   cc770.o | awk '!x[$$0]++ { print("drivers/net/can/cc770/"$$0) }' > drivers/net/can/cc770/cc770.mod
