cmd_net/can/can-gw.mod := printf '%s\n'   gw.o | awk '!x[$$0]++ { print("net/can/"$$0) }' > net/can/can-gw.mod
