cmd_sound/pci/echoaudio/snd-gina24.mod := printf '%s\n'   gina24.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-gina24.mod
