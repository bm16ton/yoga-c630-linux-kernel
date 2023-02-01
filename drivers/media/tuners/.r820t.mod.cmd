cmd_drivers/media/tuners/r820t.mod := printf '%s\n'   r820t.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/r820t.mod
