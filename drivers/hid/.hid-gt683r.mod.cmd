cmd_drivers/hid/hid-gt683r.mod := printf '%s\n'   hid-gt683r.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-gt683r.mod
