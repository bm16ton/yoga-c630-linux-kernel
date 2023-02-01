cmd_drivers/hid/hid-kye.mod := printf '%s\n'   hid-kye.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-kye.mod
