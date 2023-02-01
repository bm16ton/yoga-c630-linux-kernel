cmd_drivers/hid/hid-gyration.mod := printf '%s\n'   hid-gyration.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-gyration.mod
