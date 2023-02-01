cmd_net/netfilter/nft_queue.mod := printf '%s\n'   nft_queue.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_queue.mod
