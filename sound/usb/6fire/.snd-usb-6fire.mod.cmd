cmd_sound/usb/6fire/snd-usb-6fire.mod := printf '%s\n'   chip.o comm.o midi.o control.o firmware.o pcm.o | awk '!x[$$0]++ { print("sound/usb/6fire/"$$0) }' > sound/usb/6fire/snd-usb-6fire.mod
