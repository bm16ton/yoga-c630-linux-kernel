cmd_net/bridge/netfilter/nft_meta_bridge.mod := printf '%s\n'   nft_meta_bridge.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/nft_meta_bridge.mod
