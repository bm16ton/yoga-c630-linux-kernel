cmd_drivers/hid/hid-roccat.mod := printf '%s\n'   hid-roccat.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat.mod
