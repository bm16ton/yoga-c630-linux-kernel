cmd_drivers/staging/fbtft/fb_tinylcd.mod := printf '%s\n'   fb_tinylcd.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_tinylcd.mod
