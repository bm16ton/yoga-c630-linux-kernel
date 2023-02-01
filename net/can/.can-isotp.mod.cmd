cmd_net/can/can-isotp.mod := printf '%s\n'   isotp.o | awk '!x[$$0]++ { print("net/can/"$$0) }' > net/can/can-isotp.mod
