cmd_sound/pci/echoaudio/snd-mia.mod := printf '%s\n'   mia.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-mia.mod
