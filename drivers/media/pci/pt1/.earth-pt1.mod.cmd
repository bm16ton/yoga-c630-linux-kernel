cmd_drivers/media/pci/pt1/earth-pt1.mod := printf '%s\n'   pt1.o | awk '!x[$$0]++ { print("drivers/media/pci/pt1/"$$0) }' > drivers/media/pci/pt1/earth-pt1.mod
