cmd_drivers/net/usb/r8153_ecm.mod := printf '%s\n'   r8153_ecm.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/r8153_ecm.mod
