cmd_drivers/staging/fbtft/fb_ra8875.mod := printf '%s\n'   fb_ra8875.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_ra8875.mod
