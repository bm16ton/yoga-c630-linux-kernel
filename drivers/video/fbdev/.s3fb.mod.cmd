cmd_drivers/video/fbdev/s3fb.mod := printf '%s\n'   s3fb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/s3fb.mod
