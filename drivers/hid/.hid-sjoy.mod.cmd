cmd_drivers/hid/hid-sjoy.mod := printf '%s\n'   hid-sjoy.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-sjoy.mod
