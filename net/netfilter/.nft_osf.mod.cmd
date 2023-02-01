cmd_net/netfilter/nft_osf.mod := printf '%s\n'   nft_osf.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_osf.mod
