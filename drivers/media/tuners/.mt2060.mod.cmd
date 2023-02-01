cmd_drivers/media/tuners/mt2060.mod := printf '%s\n'   mt2060.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mt2060.mod
