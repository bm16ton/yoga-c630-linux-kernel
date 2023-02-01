cmd_sound/usb/line6/snd-usb-toneport.mod := printf '%s\n'   toneport.o | awk '!x[$$0]++ { print("sound/usb/line6/"$$0) }' > sound/usb/line6/snd-usb-toneport.mod
