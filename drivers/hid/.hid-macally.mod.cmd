cmd_drivers/hid/hid-macally.mod := printf '%s\n'   hid-macally.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-macally.mod
