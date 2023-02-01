cmd_drivers/media/pci/ivtv/ivtvfb.mod := printf '%s\n'   ivtvfb.o | awk '!x[$$0]++ { print("drivers/media/pci/ivtv/"$$0) }' > drivers/media/pci/ivtv/ivtvfb.mod
