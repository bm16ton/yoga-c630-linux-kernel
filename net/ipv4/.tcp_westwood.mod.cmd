cmd_net/ipv4/tcp_westwood.mod := printf '%s\n'   tcp_westwood.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_westwood.mod
