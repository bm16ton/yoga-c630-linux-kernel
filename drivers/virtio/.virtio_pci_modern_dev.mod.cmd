cmd_drivers/virtio/virtio_pci_modern_dev.mod := printf '%s\n'   virtio_pci_modern_dev.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_pci_modern_dev.mod
