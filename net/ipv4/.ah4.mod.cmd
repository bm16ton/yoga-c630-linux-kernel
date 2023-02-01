cmd_net/ipv4/ah4.mod := printf '%s\n'   ah4.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/ah4.mod
