cmd_sound/usb/caiaq/snd-usb-caiaq.mod := printf '%s\n'   device.o audio.o midi.o control.o input.o | awk '!x[$$0]++ { print("sound/usb/caiaq/"$$0) }' > sound/usb/caiaq/snd-usb-caiaq.mod
