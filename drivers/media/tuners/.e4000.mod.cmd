cmd_drivers/media/tuners/e4000.mod := printf '%s\n'   e4000.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/e4000.mod
