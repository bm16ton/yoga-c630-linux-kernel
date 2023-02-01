cmd_drivers/hid/hid-ntrig.mod := printf '%s\n'   hid-ntrig.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-ntrig.mod
