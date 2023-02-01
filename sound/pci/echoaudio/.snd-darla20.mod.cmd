cmd_sound/pci/echoaudio/snd-darla20.mod := printf '%s\n'   darla20.o | awk '!x[$$0]++ { print("sound/pci/echoaudio/"$$0) }' > sound/pci/echoaudio/snd-darla20.mod
