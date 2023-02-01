cmd_drivers/input/misc/uinput.mod := printf '%s\n'   uinput.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/uinput.mod
