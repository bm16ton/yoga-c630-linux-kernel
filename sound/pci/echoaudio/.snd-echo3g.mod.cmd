cmd_sound/pci/echoaudio/snd-echo3g.mod := printf '%s\n'   echo3g.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-echo3g.mod
