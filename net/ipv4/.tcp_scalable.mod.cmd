cmd_net/ipv4/tcp_scalable.mod := printf '%s\n'   tcp_scalable.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_scalable.mod
