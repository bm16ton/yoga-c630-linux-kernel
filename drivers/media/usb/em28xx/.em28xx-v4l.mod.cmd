cmd_drivers/media/usb/em28xx/em28xx-v4l.mod := printf '%s\n'   em28xx-video.o em28xx-vbi.o | awk '!x[$$0]++ { print("drivers/media/usb/em28xx/"$$0) }' > drivers/media/usb/em28xx/em28xx-v4l.mod
