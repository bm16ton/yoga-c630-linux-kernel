cmd_drivers/net/can/vcan.mod := printf '%s\n'   vcan.o | awk '!x[$$0]++ { print("drivers/net/can/"$$0) }' > drivers/net/can/vcan.mod
