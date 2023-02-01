cmd_drivers/hid/hid-cougar.mod := printf '%s\n'   hid-cougar.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-cougar.mod
