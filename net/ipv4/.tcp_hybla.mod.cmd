cmd_net/ipv4/tcp_hybla.mod := printf '%s\n'   tcp_hybla.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_hybla.mod
