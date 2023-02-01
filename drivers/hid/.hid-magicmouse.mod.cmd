cmd_drivers/hid/hid-magicmouse.mod := printf '%s\n'   hid-magicmouse.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-magicmouse.mod
