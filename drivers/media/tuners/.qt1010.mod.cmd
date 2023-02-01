cmd_drivers/media/tuners/qt1010.mod := printf '%s\n'   qt1010.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/qt1010.mod
