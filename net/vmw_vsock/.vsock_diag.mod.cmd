cmd_net/vmw_vsock/vsock_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/vmw_vsock/"$$0) }' > net/vmw_vsock/vsock_diag.mod
