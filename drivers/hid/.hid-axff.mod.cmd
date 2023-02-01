cmd_drivers/hid/hid-axff.mod := printf '%s\n'   hid-axff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-axff.mod
