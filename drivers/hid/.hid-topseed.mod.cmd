cmd_drivers/hid/hid-topseed.mod := printf '%s\n'   hid-topseed.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-topseed.mod
