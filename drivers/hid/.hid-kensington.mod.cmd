cmd_drivers/hid/hid-kensington.mod := printf '%s\n'   hid-kensington.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-kensington.mod
