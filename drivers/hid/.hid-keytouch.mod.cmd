cmd_drivers/hid/hid-keytouch.mod := printf '%s\n'   hid-keytouch.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-keytouch.mod
