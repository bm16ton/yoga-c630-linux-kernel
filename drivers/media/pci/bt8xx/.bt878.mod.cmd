cmd_drivers/media/pci/bt8xx/bt878.mod := printf '%s\n'   bt878.o | awk '!x[$$0]++ { print("drivers/media/pci/bt8xx/"$$0) }' > drivers/media/pci/bt8xx/bt878.mod
