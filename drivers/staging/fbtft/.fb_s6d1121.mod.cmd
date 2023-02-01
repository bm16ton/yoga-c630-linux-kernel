cmd_drivers/staging/fbtft/fb_s6d1121.mod := printf '%s\n'   fb_s6d1121.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_s6d1121.mod
