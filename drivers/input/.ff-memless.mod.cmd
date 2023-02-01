cmd_drivers/input/ff-memless.mod := printf '%s\n'   ff-memless.o | awk '!x[$$0]++ { print("drivers/input/"$$0) }' > drivers/input/ff-memless.mod
