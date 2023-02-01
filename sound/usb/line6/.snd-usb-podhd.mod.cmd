cmd_sound/usb/line6/snd-usb-podhd.mod := printf '%s\n'   podhd.o | awk '!x[$$0]++ { print("sound/usb/line6/"$$0) }' > sound/usb/line6/snd-usb-podhd.mod
