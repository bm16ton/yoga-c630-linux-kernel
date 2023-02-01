cmd_drivers/hid/hid-sony.mod := printf '%s\n'   hid-sony.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-sony.mod
