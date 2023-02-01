cmd_drivers/media/tuners/mt2266.mod := printf '%s\n'   mt2266.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mt2266.mod
