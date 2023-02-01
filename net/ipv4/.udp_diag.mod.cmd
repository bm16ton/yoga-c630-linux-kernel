cmd_net/ipv4/udp_diag.mod := printf '%s\n'   udp_diag.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/udp_diag.mod
