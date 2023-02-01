cmd_net/netfilter/ipset/ip_set.mod := printf '%s\n'   ip_set_core.o ip_set_getport.o pfxlen.o | awk '!x[$$0]++ { print("net/netfilter/ipset/"$$0) }' > net/netfilter/ipset/ip_set.mod
