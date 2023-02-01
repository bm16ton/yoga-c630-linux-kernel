cmd_net/ipv4/tcp_illinois.mod := printf '%s\n'   tcp_illinois.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_illinois.mod
