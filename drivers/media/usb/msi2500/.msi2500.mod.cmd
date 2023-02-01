cmd_drivers/media/usb/msi2500/msi2500.mod := printf '%s\n'   msi2500.o | awk '!x[$$0]++ { print("drivers/media/usb/msi2500/"$$0) }' > drivers/media/usb/msi2500/msi2500.mod
