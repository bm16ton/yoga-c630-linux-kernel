cmd_drivers/staging/fbtft/fb_ili9320.mod := printf '%s\n'   fb_ili9320.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_ili9320.mod
