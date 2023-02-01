cmd_drivers/staging/fbtft/fb_hx8340bn.mod := printf '%s\n'   fb_hx8340bn.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_hx8340bn.mod
