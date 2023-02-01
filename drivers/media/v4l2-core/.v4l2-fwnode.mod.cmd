cmd_drivers/media/v4l2-core/v4l2-fwnode.mod := printf '%s\n'   v4l2-fwnode.o | awk '!x[$$0]++ { print("drivers/media/v4l2-core/"$$0) }' > drivers/media/v4l2-core/v4l2-fwnode.mod
