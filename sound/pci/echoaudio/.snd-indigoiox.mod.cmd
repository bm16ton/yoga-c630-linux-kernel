cmd_sound/pci/echoaudio/snd-indigoiox.mod := printf '%s\n'   indigoiox.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-indigoiox.mod
