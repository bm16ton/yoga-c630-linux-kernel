cmd_net/ipv4/tcp_veno.mod := printf '%s\n'   tcp_veno.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tcp_veno.mod
