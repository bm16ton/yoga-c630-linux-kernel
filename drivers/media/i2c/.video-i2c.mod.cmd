cmd_drivers/media/i2c/video-i2c.mod := printf '%s\n'   video-i2c.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/video-i2c.mod
