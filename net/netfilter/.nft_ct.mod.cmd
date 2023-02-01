cmd_net/netfilter/nft_ct.mod := printf '%s\n'   nft_ct.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_ct.mod
