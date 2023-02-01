cmd_drivers/media/pci/bt8xx/dst.mod := printf '%s\n'   dst.o | awk '!x[$$0]++ { print("drivers/media/pci/bt8xx/"$$0) }' > drivers/media/pci/bt8xx/dst.mod
