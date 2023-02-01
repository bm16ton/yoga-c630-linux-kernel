cmd_drivers/hid/hid-samsung.mod := printf '%s\n'   hid-samsung.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-samsung.mod
