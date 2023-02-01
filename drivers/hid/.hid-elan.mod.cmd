cmd_drivers/hid/hid-elan.mod := printf '%s\n'   hid-elan.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-elan.mod
