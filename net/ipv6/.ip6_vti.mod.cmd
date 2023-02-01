cmd_net/ipv6/ip6_vti.mod := printf '%s\n'   ip6_vti.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/ip6_vti.mod
