cmd_drivers/media/tuners/tuner-simple.mod := printf '%s\n'   tuner-simple.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tuner-simple.mod
