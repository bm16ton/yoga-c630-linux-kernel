cmd_net/netfilter/nft_objref.mod := printf '%s\n'   nft_objref.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_objref.mod
