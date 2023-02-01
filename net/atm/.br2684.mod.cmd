cmd_net/atm/br2684.mod := printf '%s\n'   br2684.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/br2684.mod
