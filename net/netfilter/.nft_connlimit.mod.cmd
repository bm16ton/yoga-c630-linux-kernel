cmd_net/netfilter/nft_connlimit.mod := printf '%s\n'   nft_connlimit.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_connlimit.mod
