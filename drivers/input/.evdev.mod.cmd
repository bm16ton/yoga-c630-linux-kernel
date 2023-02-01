cmd_drivers/input/evdev.mod := printf '%s\n'   evdev.o | awk '!x[$$0]++ { print("drivers/input/"$$0) }' > drivers/input/evdev.mod
