cmd_net/netfilter/nft_socket.mod := printf '%s\n'   nft_socket.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nft_socket.mod
