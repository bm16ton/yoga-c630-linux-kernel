cmd_drivers/hid/hid-accutouch.mod := printf '%s\n'   hid-accutouch.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-accutouch.mod
