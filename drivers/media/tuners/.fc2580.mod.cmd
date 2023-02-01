cmd_drivers/media/tuners/fc2580.mod := printf '%s\n'   fc2580.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/fc2580.mod
