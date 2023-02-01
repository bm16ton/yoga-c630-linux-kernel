cmd_drivers/media/pci/dt3155/dt3155.mod := printf '%s\n'   dt3155.o | awk '!x[$$0]++ { print("drivers/media/pci/dt3155/"$$0) }' > drivers/media/pci/dt3155/dt3155.mod
