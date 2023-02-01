cmd_drivers/hid/hid-asus.mod := printf '%s\n'   hid-asus.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-asus.mod
