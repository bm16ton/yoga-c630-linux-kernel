cmd_drivers/hid/hid-gaff.mod := printf '%s\n'   hid-gaff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-gaff.mod
