cmd_drivers/hid/hid-gembird.mod := printf '%s\n'   hid-gembird.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-gembird.mod
