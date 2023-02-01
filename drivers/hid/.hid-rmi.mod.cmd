cmd_drivers/hid/hid-rmi.mod := printf '%s\n'   hid-rmi.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-rmi.mod
