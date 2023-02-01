cmd_drivers/video/fbdev/core/svgalib.mod := printf '%s\n'   svgalib.o | awk '!x[$$0]++ { print("drivers/video/fbdev/core/"$$0) }' > drivers/video/fbdev/core/svgalib.mod
