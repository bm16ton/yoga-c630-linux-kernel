cmd_drivers/usb/host/u132-hcd.mod := printf '%s\n'   u132-hcd.o | awk '!x[$$0]++ { print("drivers/usb/host/"$$0) }' > drivers/usb/host/u132-hcd.mod
