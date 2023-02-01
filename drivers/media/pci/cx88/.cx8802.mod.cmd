cmd_drivers/media/pci/cx88/cx8802.mod := printf '%s\n'   cx88-mpeg.o | awk '!x[$$0]++ { print("drivers/media/pci/cx88/"$$0) }' > drivers/media/pci/cx88/cx8802.mod
