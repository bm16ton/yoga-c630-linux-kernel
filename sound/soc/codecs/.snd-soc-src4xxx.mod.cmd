cmd_sound/soc/codecs/snd-soc-src4xxx.mod := printf '%s\n'   src4xxx.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-src4xxx.mod
