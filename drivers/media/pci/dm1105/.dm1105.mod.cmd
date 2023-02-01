cmd_drivers/media/pci/dm1105/dm1105.mod := printf '%s\n'   dm1105.o | awk '!x[$$0]++ { print("drivers/media/pci/dm1105/"$$0) }' > drivers/media/pci/dm1105/dm1105.mod
