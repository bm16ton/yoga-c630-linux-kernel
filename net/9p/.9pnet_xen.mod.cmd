cmd_net/9p/9pnet_xen.mod := printf '%s\n'   trans_xen.o | awk '!x[$$0]++ { print("net/9p/"$$0) }' > net/9p/9pnet_xen.mod
