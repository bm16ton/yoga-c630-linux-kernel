cmd_sound/hda/snd-intel-dspcfg.mod := printf '%s\n'   intel-dsp-config.o intel-nhlt.o | awk '!x[$$0]++ { print("sound/hda/"$$0) }' > sound/hda/snd-intel-dspcfg.mod
