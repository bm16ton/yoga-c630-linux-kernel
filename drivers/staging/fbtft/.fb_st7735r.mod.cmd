cmd_drivers/staging/fbtft/fb_st7735r.mod := printf '%s\n'   fb_st7735r.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_st7735r.mod
