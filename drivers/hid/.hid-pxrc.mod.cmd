cmd_drivers/hid/hid-pxrc.mod := printf '%s\n'   hid-pxrc.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-pxrc.mod
