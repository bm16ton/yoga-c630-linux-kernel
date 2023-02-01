cmd_drivers/uio/uio_pci_generic.mod := printf '%s\n'   uio_pci_generic.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_pci_generic.mod
