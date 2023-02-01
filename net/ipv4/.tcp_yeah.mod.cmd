cmd_net/ipv4/tcp_yeah.mod := printf '%s\n'   tcp_yeah.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_yeah.mod
