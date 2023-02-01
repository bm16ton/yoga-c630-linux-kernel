cmd_net/can/can-bcm.mod := printf '%s\n'   bcm.o | awk '!x[$$0]++ { print("net/can/"$$0) }' > net/can/can-bcm.mod
