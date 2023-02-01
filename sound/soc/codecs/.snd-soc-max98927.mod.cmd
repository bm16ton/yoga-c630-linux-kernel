cmd_sound/soc/codecs/snd-soc-max98927.mod := printf '%s\n'   max98927.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-max98927.mod
