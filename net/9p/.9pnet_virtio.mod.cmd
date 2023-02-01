cmd_net/9p/9pnet_virtio.mod := printf '%s\n'   trans_virtio.o | awk '!x[$$0]++ { print("net/9p/"$$0) }' > net/9p/9pnet_virtio.mod
