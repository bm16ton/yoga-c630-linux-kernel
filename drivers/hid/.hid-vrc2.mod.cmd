cmd_drivers/hid/hid-vrc2.mod := printf '%s\n'   hid-vrc2.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-vrc2.mod
