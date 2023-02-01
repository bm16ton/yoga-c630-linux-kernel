cmd_net/netfilter/nft_quota.mod := printf '%s\n'   nft_quota.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_quota.mod
