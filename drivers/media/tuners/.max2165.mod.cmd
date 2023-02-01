cmd_drivers/media/tuners/max2165.mod := printf '%s\n'   max2165.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/max2165.mod
