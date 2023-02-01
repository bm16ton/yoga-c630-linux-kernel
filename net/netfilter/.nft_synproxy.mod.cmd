cmd_net/netfilter/nft_synproxy.mod := printf '%s\n'   nft_synproxy.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_synproxy.mod
