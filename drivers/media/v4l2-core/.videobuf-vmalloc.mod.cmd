cmd_drivers/media/v4l2-core/videobuf-vmalloc.mod := printf '%s\n'   videobuf-vmalloc.o | awk '!x[$$0]++ { print("drivers/media/v4l2-core/"$$0) }' > drivers/media/v4l2-core/videobuf-vmalloc.mod
