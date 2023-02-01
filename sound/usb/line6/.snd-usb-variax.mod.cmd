cmd_sound/usb/line6/snd-usb-variax.mod := printf '%s\n'   variax.o | awk '!x[$$0]++ { print("sound/usb/line6/"$$0) }' > sound/usb/line6/snd-usb-variax.mod
