cmd_net/netfilter/nft_limit.mod := printf '%s\n'   nft_limit.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_limit.mod
