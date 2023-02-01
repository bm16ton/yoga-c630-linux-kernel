cmd_net/ipv4/tcp_highspeed.mod := printf '%s\n'   tcp_highspeed.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_highspeed.mod
