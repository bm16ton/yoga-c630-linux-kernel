cmd_drivers/hid/hid-roccat-isku.mod := printf '%s\n'   hid-roccat-isku.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-isku.mod
