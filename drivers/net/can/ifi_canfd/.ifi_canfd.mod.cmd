cmd_drivers/net/can/ifi_canfd/ifi_canfd.mod := printf '%s\n'   ifi_canfd.o | awk '!x[$$0]++ { print("drivers/net/can/ifi_canfd/"$$0) }' > drivers/net/can/ifi_canfd/ifi_canfd.mod
