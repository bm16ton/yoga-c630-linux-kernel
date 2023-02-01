cmd_net/netfilter/nft_reject_inet.mod := printf '%s\n'   nft_reject_inet.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_reject_inet.mod
