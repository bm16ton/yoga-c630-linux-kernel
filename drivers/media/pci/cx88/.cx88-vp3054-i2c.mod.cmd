cmd_drivers/media/pci/cx88/cx88-vp3054-i2c.mod := printf '%s\n'   cx88-vp3054-i2c.o | awk '!x[$$0]++ { print("drivers/media/pci/cx88/"$$0) }' > drivers/media/pci/cx88/cx88-vp3054-i2c.mod
