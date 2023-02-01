cmd_drivers/staging/fbtft/fb_hx8357d.mod := printf '%s\n'   fb_hx8357d.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_hx8357d.mod
