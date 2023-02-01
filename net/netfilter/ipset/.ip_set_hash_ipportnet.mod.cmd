cmd_net/netfilter/ipset/ip_set_hash_ipportnet.mod := printf '%s\n'   ip_set_hash_ipportnet.o | awk '!x[$$0]++ { print("net/netfilter/ipset/"$$0) }' > net/netfilter/ipset/ip_set_hash_ipportnet.mod
