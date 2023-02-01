cmd_net/netfilter/ipset/ip_set_hash_mac.mod := printf '%s\n'   ip_set_hash_mac.o | awk '!x[$$0]++ { print("net/netfilter/ipset/"$$0) }' > net/netfilter/ipset/ip_set_hash_mac.mod
