cmd_drivers/bus/mhi/host/mhi_pci_generic.mod := printf '%s\n'   pci_generic.o | awk '!x[$$0]++ { print("drivers/bus/mhi/host/"$$0) }' > drivers/bus/mhi/host/mhi_pci_generic.mod
