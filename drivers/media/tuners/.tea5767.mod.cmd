cmd_drivers/media/tuners/tea5767.mod := printf '%s\n'   tea5767.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tea5767.mod
