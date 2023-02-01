cmd_drivers/hid/hid-logitech-dj.mod := printf '%s\n'   hid-logitech-dj.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-logitech-dj.mod
