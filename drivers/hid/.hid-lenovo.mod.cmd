cmd_drivers/hid/hid-lenovo.mod := printf '%s\n'   hid-lenovo.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-lenovo.mod
