cmd_drivers/gpu/drm/solomon/ssd130x-i2c.mod := printf '%s\n'   ssd130x-i2c.o | awk '!x[$$0]++ { print("drivers/gpu/drm/solomon/"$$0) }' > drivers/gpu/drm/solomon/ssd130x-i2c.mod
