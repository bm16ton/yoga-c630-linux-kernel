cmd_drivers/hid/hid-roccat-koneplus.mod := printf '%s\n'   hid-roccat-koneplus.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-koneplus.mod
