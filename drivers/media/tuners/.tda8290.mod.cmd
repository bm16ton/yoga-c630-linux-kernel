cmd_drivers/media/tuners/tda8290.mod := printf '%s\n'   tda8290.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda8290.mod
