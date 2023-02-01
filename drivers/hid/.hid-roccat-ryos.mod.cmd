cmd_drivers/hid/hid-roccat-ryos.mod := printf '%s\n'   hid-roccat-ryos.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-ryos.mod
