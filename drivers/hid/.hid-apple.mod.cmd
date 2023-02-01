cmd_drivers/hid/hid-apple.mod := printf '%s\n'   hid-apple.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-apple.mod
