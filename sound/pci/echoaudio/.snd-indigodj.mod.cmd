cmd_sound/pci/echoaudio/snd-indigodj.mod := printf '%s\n'   indigodj.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-indigodj.mod
