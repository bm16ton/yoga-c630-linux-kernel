cmd_drivers/staging/fbtft/fb_uc1611.mod := printf '%s\n'   fb_uc1611.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_uc1611.mod
