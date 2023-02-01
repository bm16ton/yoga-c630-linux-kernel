cmd_drivers/media/tuners/tda827x.mod := printf '%s\n'   tda827x.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda827x.mod
