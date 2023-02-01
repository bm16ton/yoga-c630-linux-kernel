cmd_drivers/media/rc/keymaps/rc-technisat-usb2.mod := printf '%s\n'   rc-technisat-usb2.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-technisat-usb2.mod
