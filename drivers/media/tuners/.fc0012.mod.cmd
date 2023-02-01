cmd_drivers/media/tuners/fc0012.mod := printf '%s\n'   fc0012.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/fc0012.mod
