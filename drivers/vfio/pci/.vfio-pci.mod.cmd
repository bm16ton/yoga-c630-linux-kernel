cmd_drivers/vfio/pci/vfio-pci.mod := printf '%s\n'   vfio_pci.o | awk '!x[$$0]++ { print("drivers/vfio/pci/"$$0) }' > drivers/vfio/pci/vfio-pci.mod
