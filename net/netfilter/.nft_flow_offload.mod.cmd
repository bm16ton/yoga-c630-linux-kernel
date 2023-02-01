cmd_net/netfilter/nft_flow_offload.mod := printf '%s\n'   nft_flow_offload.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_flow_offload.mod
