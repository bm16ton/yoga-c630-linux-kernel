cmd_net/ipv4/ip_gre.mod := printf '%s\n'   ip_gre.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/ip_gre.mod
