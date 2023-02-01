cmd_drivers/usb/usbip/vhci-hcd.mod := printf '%s\n'   vhci_sysfs.o vhci_tx.o vhci_rx.o vhci_hcd.o | awk '!x[$$0]++ { print("drivers/usb/usbip/"$$0) }' > drivers/usb/usbip/vhci-hcd.mod
