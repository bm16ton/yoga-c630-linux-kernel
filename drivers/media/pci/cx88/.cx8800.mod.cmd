cmd_drivers/media/pci/cx88/cx8800.mod := printf '%s\n'   cx88-video.o cx88-vbi.o | awk '!x[$$0]++ { print("drivers/media/pci/cx88/"$$0) }' > drivers/media/pci/cx88/cx8800.mod
