cmd_sound/usb/misc/snd-ua101.mod := printf '%s\n'   ua101.o | awk '!x[$$0]++ { print("sound/usb/misc/"$$0) }' > sound/usb/misc/snd-ua101.mod
