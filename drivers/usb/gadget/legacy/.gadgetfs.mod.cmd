cmd_drivers/usb/gadget/legacy/gadgetfs.mod := printf '%s\n'   inode.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/gadgetfs.mod
