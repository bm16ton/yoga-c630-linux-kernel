cmd_net/ipv4/raw_diag.mod := printf '%s\n'   raw_diag.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/raw_diag.mod
