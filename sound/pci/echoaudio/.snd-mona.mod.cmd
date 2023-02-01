cmd_sound/pci/echoaudio/snd-mona.mod := printf '%s\n'   mona.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-mona.mod
