cmd_drivers/usb/host/ehci-orion.mod := printf '%s\n'   ehci-orion.o | awk '!x[$$0]++ { print("drivers/usb/host/"$$0) }' > drivers/usb/host/ehci-orion.mod
