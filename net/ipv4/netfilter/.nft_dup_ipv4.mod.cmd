cmd_net/ipv4/netfilter/nft_dup_ipv4.mod := printf '%s\n'   nft_dup_ipv4.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/nft_dup_ipv4.mod
