cmd_net/vmw_vsock/vsock.mod := printf '%s\n'   af_vsock.o af_vsock_tap.o vsock_addr.o | awk '!x[$$0]++ { print("net/vmw_vsock/"$$0) }' > net/vmw_vsock/vsock.mod
