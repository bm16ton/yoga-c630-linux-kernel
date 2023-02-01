cmd_net/netfilter/nft_reject.mod := printf '%s\n'   nft_reject.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_reject.mod
