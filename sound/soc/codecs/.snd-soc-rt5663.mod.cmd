cmd_sound/soc/codecs/snd-soc-rt5663.mod := printf '%s\n'   rt5663.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-rt5663.mod
