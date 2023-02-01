cmd_drivers/media/tuners/tea5761.mod := printf '%s\n'   tea5761.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tea5761.mod
