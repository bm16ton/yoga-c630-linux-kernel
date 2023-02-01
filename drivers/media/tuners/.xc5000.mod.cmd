cmd_drivers/media/tuners/xc5000.mod := printf '%s\n'   xc5000.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/xc5000.mod
