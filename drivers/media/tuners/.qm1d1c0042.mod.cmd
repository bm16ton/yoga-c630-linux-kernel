cmd_drivers/media/tuners/qm1d1c0042.mod := printf '%s\n'   qm1d1c0042.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/qm1d1c0042.mod
