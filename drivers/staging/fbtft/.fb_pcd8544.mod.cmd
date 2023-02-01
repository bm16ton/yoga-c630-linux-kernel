cmd_drivers/staging/fbtft/fb_pcd8544.mod := printf '%s\n'   fb_pcd8544.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fb_pcd8544.mod
