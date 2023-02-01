cmd_drivers/net/usb/asix.mod := printf '%s\n'   asix_devices.o asix_common.o ax88172a.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/asix.mod
