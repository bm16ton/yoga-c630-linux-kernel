cmd_net/netfilter/nft_masq.mod := printf '%s\n'   nft_masq.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_masq.mod
