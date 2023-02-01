cmd_net/netfilter/nft_tproxy.mod := printf '%s\n'   nft_tproxy.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_tproxy.mod
