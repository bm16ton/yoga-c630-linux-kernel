cmd_drivers/virtio/virtio_dma_buf.mod := printf '%s\n'   virtio_dma_buf.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_dma_buf.mod
