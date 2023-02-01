cmd_drivers/hid/hid-maltron.mod := printf '%s\n'   hid-maltron.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-maltron.mod
