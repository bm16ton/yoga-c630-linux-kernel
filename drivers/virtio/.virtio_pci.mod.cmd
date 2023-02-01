cmd_drivers/virtio/virtio_pci.mod := printf '%s\n'   virtio_pci_modern.o virtio_pci_common.o virtio_pci_legacy.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_pci.mod
