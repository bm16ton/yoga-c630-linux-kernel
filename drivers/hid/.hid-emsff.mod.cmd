cmd_drivers/hid/hid-emsff.mod := printf '%s\n'   hid-emsff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-emsff.mod
