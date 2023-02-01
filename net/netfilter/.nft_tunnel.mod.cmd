cmd_net/netfilter/nft_tunnel.mod := printf '%s\n'   nft_tunnel.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_tunnel.mod
