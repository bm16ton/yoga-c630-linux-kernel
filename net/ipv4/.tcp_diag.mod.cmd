cmd_net/ipv4/tcp_diag.mod := printf '%s\n'   tcp_diag.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_diag.mod
