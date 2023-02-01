cmd_sound/usb/snd-usbmidi-lib.mod := printf '%s\n'   midi.o | awk '!x[$$0]++ { print("sound/usb/"$$0) }' > sound/usb/snd-usbmidi-lib.mod
