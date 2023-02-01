cmd_net/ipv4/tcp_bic.mod := printf '%s\n'   tcp_bic.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_bic.mod
