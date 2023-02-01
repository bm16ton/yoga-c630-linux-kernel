cmd_drivers/net/can/flexcan/flexcan.mod := printf '%s\n'   flexcan-core.o flexcan-ethtool.o | awk '!x[$$0]++ { print("drivers/net/can/flexcan/"$$0) }' > drivers/net/can/flexcan/flexcan.mod
