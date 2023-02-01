cmd_drivers/pci/pcie/aer_inject.mod := printf '%s\n'   aer_inject.o | awk '!x[$$0]++ { print("drivers/pci/pcie/"$$0) }' > drivers/pci/pcie/aer_inject.mod
