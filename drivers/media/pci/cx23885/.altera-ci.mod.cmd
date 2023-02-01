cmd_drivers/media/pci/cx23885/altera-ci.mod := printf '%s\n'   altera-ci.o | awk '!x[$$0]++ { print("drivers/media/pci/cx23885/"$$0) }' > drivers/media/pci/cx23885/altera-ci.mod
