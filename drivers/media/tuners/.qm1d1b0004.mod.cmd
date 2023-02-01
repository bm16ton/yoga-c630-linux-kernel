cmd_drivers/media/tuners/qm1d1b0004.mod := printf '%s\n'   qm1d1b0004.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/qm1d1b0004.mod
