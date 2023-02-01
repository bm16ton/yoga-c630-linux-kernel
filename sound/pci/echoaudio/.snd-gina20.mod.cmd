cmd_sound/pci/echoaudio/snd-gina20.mod := printf '%s\n'   gina20.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-gina20.mod
