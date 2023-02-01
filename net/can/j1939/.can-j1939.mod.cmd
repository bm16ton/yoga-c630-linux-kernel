cmd_net/can/j1939/can-j1939.mod := printf '%s\n'   address-claim.o bus.o main.o socket.o transport.o | awk '!x[$$0]++ { print("net/can/j1939/"$$0) }' > net/can/j1939/can-j1939.mod
