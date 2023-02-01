cmd_drivers/media/tuners/msi001.mod := printf '%s\n'   msi001.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/msi001.mod
