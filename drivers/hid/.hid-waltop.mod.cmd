cmd_drivers/hid/hid-waltop.mod := printf '%s\n'   hid-waltop.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-waltop.mod
