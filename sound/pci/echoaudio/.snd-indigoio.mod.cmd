cmd_sound/pci/echoaudio/snd-indigoio.mod := printf '%s\n'   indigoio.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-indigoio.mod
