cmd_drivers/media/tuners/si2157.mod := printf '%s\n'   si2157.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/si2157.mod
