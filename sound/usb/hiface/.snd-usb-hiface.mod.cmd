cmd_sound/usb/hiface/snd-usb-hiface.mod := printf '%s\n'   chip.o pcm.o | awk '!x[$$0]++ { print("sound/usb/hiface/"$$0) }' > sound/usb/hiface/snd-usb-hiface.mod
