cmd_drivers/media/tuners/xc2028.mod := printf '%s\n'   xc2028.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/xc2028.mod
