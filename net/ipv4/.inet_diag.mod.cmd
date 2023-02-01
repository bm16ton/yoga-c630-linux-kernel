cmd_net/ipv4/inet_diag.mod := printf '%s\n'   inet_diag.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/inet_diag.mod
