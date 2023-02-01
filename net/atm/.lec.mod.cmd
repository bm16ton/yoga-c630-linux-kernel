cmd_net/atm/lec.mod := printf '%s\n'   lec.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/lec.mod
