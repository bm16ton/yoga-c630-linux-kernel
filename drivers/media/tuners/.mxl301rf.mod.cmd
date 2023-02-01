cmd_drivers/media/tuners/mxl301rf.mod := printf '%s\n'   mxl301rf.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mxl301rf.mod
