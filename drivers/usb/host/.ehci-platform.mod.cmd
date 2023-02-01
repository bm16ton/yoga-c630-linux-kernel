cmd_drivers/usb/host/ehci-platform.mod := printf '%s\n'   ehci-platform.o | awk '!x[$$0]++ { print("drivers/usb/host/"$$0) }' > drivers/usb/host/ehci-platform.mod
