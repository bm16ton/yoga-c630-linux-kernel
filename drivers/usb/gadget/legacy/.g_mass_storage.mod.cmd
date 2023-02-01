cmd_drivers/usb/gadget/legacy/g_mass_storage.mod := printf '%s\n'   mass_storage.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_mass_storage.mod
