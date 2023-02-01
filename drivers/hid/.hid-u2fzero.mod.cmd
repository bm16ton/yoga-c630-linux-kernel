cmd_drivers/hid/hid-u2fzero.mod := printf '%s\n'   hid-u2fzero.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-u2fzero.mod
