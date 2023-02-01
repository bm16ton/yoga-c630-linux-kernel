cmd_net/ipv4/xfrm4_tunnel.mod := printf '%s\n'   xfrm4_tunnel.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/xfrm4_tunnel.mod
