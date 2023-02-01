cmd_drivers/media/pci/cx88/cx88-dvb.mod := printf '%s\n'   cx88-dvb.o | awk '!x[$$0]++ { print("drivers/media/pci/cx88/"$$0) }' > drivers/media/pci/cx88/cx88-dvb.mod
