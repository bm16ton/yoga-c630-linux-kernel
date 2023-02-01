cmd_drivers/staging/fbtft/fb_ili9340.mod := printf '%s\n'   fb_ili9340.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_ili9340.mod
