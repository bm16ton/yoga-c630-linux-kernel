cmd_drivers/media/pci/pt3/earth-pt3.mod := printf '%s\n'   pt3.o pt3_i2c.o pt3_dma.o | awk '!x[$$0]++ { print("drivers/media/pci/pt3/"$$0) }' > drivers/media/pci/pt3/earth-pt3.mod
