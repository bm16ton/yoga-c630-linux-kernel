cmd_sound/soc/codecs/snd-soc-es8326.mod := printf '%s\n'   es8326.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-es8326.mod
