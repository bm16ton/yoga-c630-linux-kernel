cmd_drivers/media/i2c/vp27smpx.mod := printf '%s\n'   vp27smpx.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/vp27smpx.mod
