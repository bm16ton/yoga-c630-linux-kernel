cmd_drivers/media/pci/pluto2/pluto2.mod := printf '%s\n'   pluto2.o | awk '!x[$$0]++ { print("drivers/media/pci/pluto2/"$$0) }' > drivers/media/pci/pluto2/pluto2.mod
