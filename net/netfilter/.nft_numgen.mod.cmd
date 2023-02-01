cmd_net/netfilter/nft_numgen.mod := printf '%s\n'   nft_numgen.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_numgen.mod
