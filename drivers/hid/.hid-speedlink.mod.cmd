cmd_drivers/hid/hid-speedlink.mod := printf '%s\n'   hid-speedlink.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-speedlink.mod
