cmd_drivers/media/tuners/it913x.mod := printf '%s\n'   it913x.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/it913x.mod
