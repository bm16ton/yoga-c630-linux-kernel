cmd_sound/pci/echoaudio/snd-layla24.mod := printf '%s\n'   layla24.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-layla24.mod
