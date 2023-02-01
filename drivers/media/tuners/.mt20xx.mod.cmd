cmd_drivers/media/tuners/mt20xx.mod := printf '%s\n'   mt20xx.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mt20xx.mod
