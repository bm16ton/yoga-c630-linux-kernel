cmd_sound/pci/pcxhr/snd-pcxhr.mod := printf '%s\n'   pcxhr.o pcxhr_hwdep.o pcxhr_mixer.o pcxhr_core.o pcxhr_mix22.o | awk '!x[$$0]++ { print("sound/pci/pcxhr/"$$0) }' > sound/pci/pcxhr/snd-pcxhr.mod
