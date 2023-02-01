cmd_drivers/hid/hid-elecom.mod := printf '%s\n'   hid-elecom.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-elecom.mod
