cmd_drivers/media/v4l2-core/tuner.mod := printf '%s\n'   tuner-core.o | awk '!x[$$0]++ { print("drivers/media/v4l2-core/"$$0) }' > drivers/media/v4l2-core/tuner.mod
