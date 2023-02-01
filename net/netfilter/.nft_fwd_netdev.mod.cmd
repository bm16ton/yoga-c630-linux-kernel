cmd_net/netfilter/nft_fwd_netdev.mod := printf '%s\n'   nft_fwd_netdev.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_fwd_netdev.mod
