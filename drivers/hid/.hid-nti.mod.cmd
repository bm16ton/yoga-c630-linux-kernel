cmd_drivers/hid/hid-nti.mod := printf '%s\n'   hid-nti.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-nti.mod
