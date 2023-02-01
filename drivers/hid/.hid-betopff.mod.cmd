cmd_drivers/hid/hid-betopff.mod := printf '%s\n'   hid-betopff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-betopff.mod
