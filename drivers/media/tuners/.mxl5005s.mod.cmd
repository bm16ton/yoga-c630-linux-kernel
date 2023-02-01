cmd_drivers/media/tuners/mxl5005s.mod := printf '%s\n'   mxl5005s.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mxl5005s.mod
