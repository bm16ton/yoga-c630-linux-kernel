cmd_drivers/net/can/vxcan.mod := printf '%s\n'   vxcan.o | awk '!x[$$0]++ { print("drivers/net/can/"$$0) }' > drivers/net/can/vxcan.mod
