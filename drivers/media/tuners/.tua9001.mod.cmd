cmd_drivers/media/tuners/tua9001.mod := printf '%s\n'   tua9001.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tua9001.mod
