cmd_sound/pci/lola/snd-lola.mod := printf '%s\n'   lola.o lola_pcm.o lola_clock.o lola_mixer.o | awk '!x[$$0]++ { print("sound/pci/lola/"$$0) }' > sound/pci/lola/snd-lola.mod
