cmd_drivers/hid/hid-prodikeys.mod := printf '%s\n'   hid-prodikeys.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-prodikeys.mod
