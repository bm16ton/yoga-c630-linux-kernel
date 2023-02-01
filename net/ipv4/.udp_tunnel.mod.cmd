cmd_net/ipv4/udp_tunnel.mod := printf '%s\n'   udp_tunnel_core.o udp_tunnel_nic.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/udp_tunnel.mod
