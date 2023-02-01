cmd_net/netfilter/nft_redir.mod := printf '%s\n'   nft_redir.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_redir.mod
