cmd_drivers/video/fbdev/ssd1307fb.mod := printf '%s\n'   ssd1307fb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/ssd1307fb.mod
