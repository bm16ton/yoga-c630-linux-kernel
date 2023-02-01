cmd_drivers/net/can/slcan/slcan.mod := printf '%s\n'   slcan-core.o slcan-ethtool.o | awk '!x[$$0]++ { print("drivers/net/can/slcan/"$$0) }' > drivers/net/can/slcan/slcan.mod
