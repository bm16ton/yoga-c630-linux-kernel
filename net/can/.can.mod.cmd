cmd_net/can/can.mod := printf '%s\n'   af_can.o proc.o | awk '!x[$$0]++ { print("net/can/"$$0) }' > net/can/can.mod
