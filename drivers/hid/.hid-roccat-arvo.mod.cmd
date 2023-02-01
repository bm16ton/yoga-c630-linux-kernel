cmd_drivers/hid/hid-roccat-arvo.mod := printf '%s\n'   hid-roccat-arvo.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-roccat-arvo.mod
