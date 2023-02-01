cmd_drivers/usb/usbip/usbip-host.mod := printf '%s\n'   stub_dev.o stub_main.o stub_rx.o stub_tx.o | awk '!x[$$0]++ { print("drivers/usb/usbip/"$$0) }' > drivers/usb/usbip/usbip-host.mod
