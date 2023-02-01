cmd_drivers/hid/hid-xinmo.mod := printf '%s\n'   hid-xinmo.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-xinmo.mod
