cmd_drivers/media/tuners/tuner-types.mod := printf '%s\n'   tuner-types.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tuner-types.mod
