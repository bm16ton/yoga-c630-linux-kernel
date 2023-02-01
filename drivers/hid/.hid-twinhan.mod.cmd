cmd_drivers/hid/hid-twinhan.mod := printf '%s\n'   hid-twinhan.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-twinhan.mod
