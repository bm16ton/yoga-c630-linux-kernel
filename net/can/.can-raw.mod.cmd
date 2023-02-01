cmd_net/can/can-raw.mod := printf '%s\n'   raw.o | awk '!x[$$0]++ { print("net/can/"$$0) }' > net/can/can-raw.mod
