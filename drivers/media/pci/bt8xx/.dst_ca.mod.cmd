cmd_drivers/media/pci/bt8xx/dst_ca.mod := printf '%s\n'   dst_ca.o | awk '!x[$$0]++ { print("drivers/media/pci/bt8xx/"$$0) }' > drivers/media/pci/bt8xx/dst_ca.mod
