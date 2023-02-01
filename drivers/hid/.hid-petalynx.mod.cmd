cmd_drivers/hid/hid-petalynx.mod := printf '%s\n'   hid-petalynx.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-petalynx.mod
