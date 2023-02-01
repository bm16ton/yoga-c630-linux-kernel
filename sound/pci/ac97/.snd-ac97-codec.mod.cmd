cmd_sound/pci/ac97/snd-ac97-codec.mod := printf '%s\n'   ac97_codec.o ac97_pcm.o ac97_proc.o | awk '!x[$$0]++ { print("sound/pci/ac97/"$$0) }' > sound/pci/ac97/snd-ac97-codec.mod
