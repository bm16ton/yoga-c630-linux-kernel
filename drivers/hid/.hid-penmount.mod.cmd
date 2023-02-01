cmd_drivers/hid/hid-penmount.mod := printf '%s\n'   hid-penmount.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-penmount.mod
