cmd_drivers/hid/hid-roccat-savu.mod := printf '%s\n'   hid-roccat-savu.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-savu.mod
