cmd_net/bridge/netfilter/nft_reject_bridge.mod := printf '%s\n'   nft_reject_bridge.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/nft_reject_bridge.mod
