cmd_drivers/hid/hid-roccat-konepure.mod := printf '%s\n'   hid-roccat-konepure.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-konepure.mod
