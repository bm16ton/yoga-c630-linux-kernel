cmd_drivers/usb/usbip/usbip-core.mod := printf '%s\n'   usbip_common.o usbip_event.o | awk '!x[$$0]++ { print("drivers/usb/usbip/"$$0) }' > drivers/usb/usbip/usbip-core.mod
