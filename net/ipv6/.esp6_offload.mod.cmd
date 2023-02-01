cmd_net/ipv6/esp6_offload.mod := printf '%s\n'   esp6_offload.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/esp6_offload.mod
