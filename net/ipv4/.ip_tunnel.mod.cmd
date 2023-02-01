cmd_net/ipv4/ip_tunnel.mod := printf '%s\n'   ip_tunnel.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/ip_tunnel.mod
