cmd_net/netfilter/ipset/ip_set_list_set.mod := printf '%s\n'   ip_set_list_set.o | awk '!x[$$0]++ { print("net/netfilter/ipset/"$$0) }' > net/netfilter/ipset/ip_set_list_set.mod
