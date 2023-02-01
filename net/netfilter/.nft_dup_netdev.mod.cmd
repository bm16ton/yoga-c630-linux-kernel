cmd_net/netfilter/nft_dup_netdev.mod := printf '%s\n'   nft_dup_netdev.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_dup_netdev.mod
