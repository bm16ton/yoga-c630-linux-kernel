cmd_drivers/usb/gadget/legacy/g_audio.mod := printf '%s\n'   audio.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_audio.mod
