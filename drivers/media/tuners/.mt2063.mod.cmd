cmd_drivers/media/tuners/mt2063.mod := printf '%s\n'   mt2063.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mt2063.mod
