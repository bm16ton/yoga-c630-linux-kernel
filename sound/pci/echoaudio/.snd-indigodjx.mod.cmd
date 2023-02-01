cmd_sound/pci/echoaudio/snd-indigodjx.mod := printf '%s\n'   indigodjx.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-indigodjx.mod
