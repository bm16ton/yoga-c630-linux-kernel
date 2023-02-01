cmd_net/netfilter/nft_compat.mod := printf '%s\n'   nft_compat.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_compat.mod
