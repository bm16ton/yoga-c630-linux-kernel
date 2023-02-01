cmd_drivers/hid/hid-roccat-pyra.mod := printf '%s\n'   hid-roccat-pyra.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-pyra.mod
