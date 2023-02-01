cmd_drivers/usb/serial/upd78f0730.mod := printf '%s\n'   upd78f0730.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/upd78f0730.mod
