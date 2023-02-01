cmd_drivers/input/misc/cm109.mod := printf '%s\n'   cm109.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/cm109.mod
