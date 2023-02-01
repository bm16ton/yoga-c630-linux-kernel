cmd_net/vmw_vsock/vsock_loopback.mod := printf '%s\n'   vsock_loopback.o | awk '!x[$$0]++ { print("net/vmw_vsock/"$$0) }' > net/vmw_vsock/vsock_loopback.mod
