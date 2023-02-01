cmd_drivers/net/can/c_can/c_can.mod := printf '%s\n'   c_can_ethtool.o c_can_main.o | awk '!x[$$0]++ { print("drivers/net/can/c_can/"$$0) }' > drivers/net/can/c_can/c_can.mod
