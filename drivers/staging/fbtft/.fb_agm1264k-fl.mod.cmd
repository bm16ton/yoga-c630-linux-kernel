cmd_drivers/staging/fbtft/fb_agm1264k-fl.mod := printf '%s\n'   fb_agm1264k-fl.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_agm1264k-fl.mod
