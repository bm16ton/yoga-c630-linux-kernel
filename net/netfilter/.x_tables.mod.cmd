cmd_net/netfilter/x_tables.mod := printf '%s\n'   x_tables.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/x_tables.mod
