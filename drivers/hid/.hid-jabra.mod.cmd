cmd_drivers/hid/hid-jabra.mod := printf '%s\n'   hid-jabra.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-jabra.mod
