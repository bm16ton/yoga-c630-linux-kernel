cmd_net/atm/pppoatm.mod := printf '%s\n'   pppoatm.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/pppoatm.mod
