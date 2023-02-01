cmd_sound/usb/bcd2000/snd-bcd2000.mod := printf '%s\n'   bcd2000.o | awk '!x[$$0]++ { print("sound/usb/bcd2000/"$$0) }' > sound/usb/bcd2000/snd-bcd2000.mod
