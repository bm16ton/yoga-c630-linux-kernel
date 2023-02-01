cmd_drivers/hid/hid-roccat-kovaplus.mod := printf '%s\n'   hid-roccat-kovaplus.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-kovaplus.mod
