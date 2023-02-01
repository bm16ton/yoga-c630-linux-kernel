cmd_sound/pci/echoaudio/snd-indigo.mod := printf '%s\n'   indigo.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-indigo.mod
