cmd_drivers/hid/hid-cp2112.mod := printf '%s\n'   hid-cp2112.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-cp2112.mod
