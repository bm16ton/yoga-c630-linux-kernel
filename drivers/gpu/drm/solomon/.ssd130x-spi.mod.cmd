cmd_drivers/gpu/drm/solomon/ssd130x-spi.mod := printf '%s\n'   ssd130x-spi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/solomon/"$$0) }' > drivers/gpu/drm/solomon/ssd130x-spi.mod
