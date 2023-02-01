cmd_drivers/usb/gadget/legacy/g_webcam.mod := printf '%s\n'   webcam.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_webcam.mod
