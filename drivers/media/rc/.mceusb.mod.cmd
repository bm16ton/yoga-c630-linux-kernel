cmd_drivers/media/rc/mceusb.mod := printf '%s\n'   mceusb.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/mceusb.mod
