cmd_net/vmw_vsock/vmw_vsock_virtio_transport.mod := printf '%s\n'   virtio_transport.o | awk '!x[$$0]++ { print("net/vmw_vsock/"$$0) }' > net/vmw_vsock/vmw_vsock_virtio_transport.mod
