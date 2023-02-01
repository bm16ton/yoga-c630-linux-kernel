cmd_sound/soc/codecs/snd-soc-simple-amplifier.mod := printf '%s\n'   simple-amplifier.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-simple-amplifier.mod
