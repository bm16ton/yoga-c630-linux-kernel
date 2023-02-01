cmd_drivers/hid/hid-plantronics.mod := printf '%s\n'   hid-plantronics.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-plantronics.mod
