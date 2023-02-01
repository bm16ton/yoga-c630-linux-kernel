cmd_drivers/hid/hid-bigbenff.mod := printf '%s\n'   hid-bigbenff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-bigbenff.mod
