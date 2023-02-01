cmd_drivers/media/tuners/mt2131.mod := printf '%s\n'   mt2131.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mt2131.mod
