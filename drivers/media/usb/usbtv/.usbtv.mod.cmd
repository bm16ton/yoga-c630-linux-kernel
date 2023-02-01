cmd_drivers/media/usb/usbtv/usbtv.mod := printf '%s\n'   usbtv-core.o usbtv-video.o usbtv-audio.o | awk '!x[$$0]++ { print("drivers/media/usb/usbtv/"$$0) }' > drivers/media/usb/usbtv/usbtv.mod
