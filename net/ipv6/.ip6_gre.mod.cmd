cmd_net/ipv6/ip6_gre.mod := printf '%s\n'   ip6_gre.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/ip6_gre.mod
