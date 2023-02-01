cmd_drivers/hid/hid-lg-g15.mod := printf '%s\n'   hid-lg-g15.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-lg-g15.mod
