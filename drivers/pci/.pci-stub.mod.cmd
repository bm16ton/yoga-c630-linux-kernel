cmd_drivers/pci/pci-stub.mod := printf '%s\n'   pci-stub.o | awk '!x[$$0]++ { print("drivers/pci/"$$0) }' > drivers/pci/pci-stub.mod
