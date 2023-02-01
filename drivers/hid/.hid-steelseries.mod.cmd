cmd_drivers/hid/hid-steelseries.mod := printf '%s\n'   hid-steelseries.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-steelseries.mod
