cmd_drivers/staging/fbtft/fb_st7789v.mod := printf '%s\n'   fb_st7789v.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_st7789v.mod
