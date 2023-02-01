cmd_drivers/hid/hid-roccat-kone.mod := printf '%s\n'   hid-roccat-kone.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-kone.mod
