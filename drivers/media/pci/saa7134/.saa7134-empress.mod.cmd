cmd_drivers/media/pci/saa7134/saa7134-empress.mod := printf '%s\n'   saa7134-empress.o | awk '!x[$$0]++ { print("drivers/media/pci/saa7134/"$$0) }' > drivers/media/pci/saa7134/saa7134-empress.mod
