cmd_drivers/hid/hid-tmff.mod := printf '%s\n'   hid-tmff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-tmff.mod
