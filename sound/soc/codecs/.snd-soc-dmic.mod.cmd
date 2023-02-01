cmd_sound/soc/codecs/snd-soc-dmic.mod := printf '%s\n'   dmic.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-dmic.mod
