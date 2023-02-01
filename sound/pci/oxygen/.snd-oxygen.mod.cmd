cmd_sound/pci/oxygen/snd-oxygen.mod := printf '%s\n'   oxygen.o xonar_dg_mixer.o xonar_dg.o | awk '!x[$$0]++ { print("sound/pci/oxygen/"$$0) }' > sound/pci/oxygen/snd-oxygen.mod
