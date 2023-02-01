cmd_drivers/media/v4l2-core/videobuf-core.mod := printf '%s\n'   videobuf-core.o | awk '!x[$$0]++ { print("drivers/media/v4l2-core/"$$0) }' > drivers/media/v4l2-core/videobuf-core.mod
