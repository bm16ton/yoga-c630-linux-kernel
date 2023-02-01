cmd_net/ipv4/tcp_vegas.mod := printf '%s\n'   tcp_vegas.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_vegas.mod
