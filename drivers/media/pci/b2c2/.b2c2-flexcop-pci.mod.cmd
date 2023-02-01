cmd_drivers/media/pci/b2c2/b2c2-flexcop-pci.mod := printf '%s\n'   flexcop-dma.o flexcop-pci.o | awk '!x[$$0]++ { print("drivers/media/pci/b2c2/"$$0) }' > drivers/media/pci/b2c2/b2c2-flexcop-pci.mod
