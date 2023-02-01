cmd_sound/pci/echoaudio/snd-layla20.mod := printf '%s\n'   layla20.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-layla20.mod
