cmd_net/ipv4/tcp_htcp.mod := printf '%s\n'   tcp_htcp.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_htcp.mod
