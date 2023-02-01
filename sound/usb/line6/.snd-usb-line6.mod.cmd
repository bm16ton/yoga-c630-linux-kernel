cmd_sound/usb/line6/snd-usb-line6.mod := printf '%s\n'   capture.o driver.o midi.o midibuf.o pcm.o playback.o | awk '!x[$$0]++ { print("sound/usb/line6/"$$0) }' > sound/usb/line6/snd-usb-line6.mod
