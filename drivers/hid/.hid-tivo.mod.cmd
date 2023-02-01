cmd_drivers/hid/hid-tivo.mod := printf '%s\n'   hid-tivo.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-tivo.mod
