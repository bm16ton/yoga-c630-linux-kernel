cmd_sound/soc/codecs/snd-soc-wcd934x.mod := printf '%s\n'   wcd-clsh-v2.o wcd934x.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-wcd934x.mod
