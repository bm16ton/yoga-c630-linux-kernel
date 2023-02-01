cmd_drivers/hid/hid-gfrm.mod := printf '%s\n'   hid-gfrm.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-gfrm.mod
