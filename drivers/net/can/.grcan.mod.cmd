cmd_drivers/net/can/grcan.mod := printf '%s\n'   grcan.o | awk '!x[$$0]++ { print("drivers/net/can/"$$0) }' > drivers/net/can/grcan.mod
