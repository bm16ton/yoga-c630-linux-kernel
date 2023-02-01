cmd_drivers/input/joydev.mod := printf '%s\n'   joydev.o | awk '!x[$$0]++ { print("drivers/input/"$$0) }' > drivers/input/joydev.mod
