cmd_drivers/media/tuners/tda9887.mod := printf '%s\n'   tda9887.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda9887.mod
