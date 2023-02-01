cmd_drivers/media/tuners/xc4000.mod := printf '%s\n'   xc4000.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/xc4000.mod
