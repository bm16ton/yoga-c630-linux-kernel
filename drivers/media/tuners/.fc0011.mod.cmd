cmd_drivers/media/tuners/fc0011.mod := printf '%s\n'   fc0011.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/fc0011.mod
