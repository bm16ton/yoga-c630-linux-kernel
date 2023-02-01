cmd_drivers/media/mc/mc.mod := printf '%s\n'   mc-device.o mc-devnode.o mc-entity.o mc-request.o mc-dev-allocator.o | awk '!x[$$0]++ { print("drivers/media/mc/"$$0) }' > drivers/media/mc/mc.mod
