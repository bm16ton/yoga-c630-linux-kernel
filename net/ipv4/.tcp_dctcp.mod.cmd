cmd_net/ipv4/tcp_dctcp.mod := printf '%s\n'   tcp_dctcp.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_dctcp.mod
