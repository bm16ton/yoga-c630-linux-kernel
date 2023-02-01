cmd_net/ipv4/fou.mod := printf '%s\n'   fou.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/fou.mod
