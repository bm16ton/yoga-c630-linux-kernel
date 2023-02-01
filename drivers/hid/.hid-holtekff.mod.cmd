cmd_drivers/hid/hid-holtekff.mod := printf '%s\n'   hid-holtekff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-holtekff.mod
