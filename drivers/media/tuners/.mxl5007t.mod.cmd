cmd_drivers/media/tuners/mxl5007t.mod := printf '%s\n'   mxl5007t.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mxl5007t.mod
