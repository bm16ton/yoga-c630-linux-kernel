cmd_drivers/input/mouse/synaptics_usb.mod := printf '%s\n'   synaptics_usb.o | awk '!x[$$0]++ { print("drivers/input/mouse/"$$0) }' > drivers/input/mouse/synaptics_usb.mod
