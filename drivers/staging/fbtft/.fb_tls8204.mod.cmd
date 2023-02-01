cmd_drivers/staging/fbtft/fb_tls8204.mod := printf '%s\n'   fb_tls8204.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_tls8204.mod
