cmd_sound/pci/echoaudio/snd-darla24.mod := printf '%s\n'   darla24.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-darla24.mod
