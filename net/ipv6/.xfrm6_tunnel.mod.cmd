cmd_net/ipv6/xfrm6_tunnel.mod := printf '%s\n'   xfrm6_tunnel.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/xfrm6_tunnel.mod
