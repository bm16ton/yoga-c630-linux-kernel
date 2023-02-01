cmd_drivers/staging/fbtft/fb_ssd1331.mod := printf '%s\n'   fb_ssd1331.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_ssd1331.mod
