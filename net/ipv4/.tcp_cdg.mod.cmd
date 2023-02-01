cmd_net/ipv4/tcp_cdg.mod := printf '%s\n'   tcp_cdg.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_cdg.mod
