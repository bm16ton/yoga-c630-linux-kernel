cmd_drivers/media/pci/bt8xx/dvb-bt8xx.mod := printf '%s\n'   dvb-bt8xx.o | awk '!x[$$0]++ { print("drivers/media/pci/bt8xx/"$$0) }' > drivers/media/pci/bt8xx/dvb-bt8xx.mod
