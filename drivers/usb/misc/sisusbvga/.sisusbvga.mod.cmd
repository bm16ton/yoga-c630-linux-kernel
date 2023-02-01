cmd_drivers/usb/misc/sisusbvga/sisusbvga.mod := printf '%s\n'   sisusb.o | awk '!x[$$0]++ { print("drivers/usb/misc/sisusbvga/"$$0) }' > drivers/usb/misc/sisusbvga/sisusbvga.mod
