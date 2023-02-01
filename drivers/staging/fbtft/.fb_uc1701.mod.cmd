cmd_drivers/staging/fbtft/fb_uc1701.mod := printf '%s\n'   fb_uc1701.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_uc1701.mod
