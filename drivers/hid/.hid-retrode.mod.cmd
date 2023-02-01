cmd_drivers/hid/hid-retrode.mod := printf '%s\n'   hid-retrode.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-retrode.mod
