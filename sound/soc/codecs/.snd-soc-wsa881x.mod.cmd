cmd_sound/soc/codecs/snd-soc-wsa881x.mod := printf '%s\n'   wsa881x.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-wsa881x.mod
