cmd_drivers/hid/hid-microsoft.mod := printf '%s\n'   hid-microsoft.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-microsoft.mod
