cmd_drivers/staging/fbtft/fb_hx8347d.mod := printf '%s\n'   fb_hx8347d.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_hx8347d.mod
