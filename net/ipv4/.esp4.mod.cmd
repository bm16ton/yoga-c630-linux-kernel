cmd_net/ipv4/esp4.mod := printf '%s\n'   esp4.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/esp4.mod
