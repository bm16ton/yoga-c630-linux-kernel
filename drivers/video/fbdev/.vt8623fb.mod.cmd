cmd_drivers/video/fbdev/vt8623fb.mod := printf '%s\n'   vt8623fb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/vt8623fb.mod
