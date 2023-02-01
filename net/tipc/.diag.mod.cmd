cmd_net/tipc/diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/tipc/"$$0) }' > net/tipc/diag.mod
