cmd_net/ipv4/tcp_lp.mod := printf '%s\n'   tcp_lp.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_lp.mod
