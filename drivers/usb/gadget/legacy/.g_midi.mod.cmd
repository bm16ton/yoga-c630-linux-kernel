cmd_drivers/usb/gadget/legacy/g_midi.mod := printf '%s\n'   gmidi.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_midi.mod
