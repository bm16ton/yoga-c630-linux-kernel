cmd_drivers/hid/hid-logitech-hidpp.mod := printf '%s\n'   hid-logitech-hidpp.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-logitech-hidpp.mod
