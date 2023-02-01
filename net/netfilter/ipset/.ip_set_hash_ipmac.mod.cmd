cmd_net/netfilter/ipset/ip_set_hash_ipmac.mod := printf '%s\n'   ip_set_hash_ipmac.o | awk '!x[$$0]++ { print("net/netfilter/ipset/"$$0) }' > net/netfilter/ipset/ip_set_hash_ipmac.mod
