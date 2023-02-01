cmd_drivers/pci/pci-pf-stub.mod := printf '%s\n'   pci-pf-stub.o | awk '!x[$$0]++ { print("drivers/pci/"$$0) }' > drivers/pci/pci-pf-stub.mod
