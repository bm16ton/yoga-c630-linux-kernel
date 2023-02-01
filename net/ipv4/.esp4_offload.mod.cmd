cmd_net/ipv4/esp4_offload.mod := printf '%s\n'   esp4_offload.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/esp4_offload.mod
