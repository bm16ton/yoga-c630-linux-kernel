cmd_drivers/hid/hid-roccat-lua.mod := printf '%s\n'   hid-roccat-lua.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-lua.mod
