cmd_drivers/hid/hid-roccat-common.mod := printf '%s\n'   hid-roccat-common.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-common.mod
