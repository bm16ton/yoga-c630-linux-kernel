cmd_net/netfilter/nft_nat.mod := printf '%s\n'   nft_nat.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_nat.mod
