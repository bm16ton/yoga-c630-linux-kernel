cmd_drivers/hid/hid-viewsonic.mod := printf '%s\n'   hid-viewsonic.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-viewsonic.mod
