cmd_drivers/hid/hid-multitouch.mod := printf '%s\n'   hid-multitouch.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-multitouch.mod
