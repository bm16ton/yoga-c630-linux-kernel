cmd_sound/usb/line6/snd-usb-pod.mod := printf '%s\n'   pod.o | awk '!x[$$0]++ { print("sound/usb/line6/"$$0) }' > sound/usb/line6/snd-usb-pod.mod
