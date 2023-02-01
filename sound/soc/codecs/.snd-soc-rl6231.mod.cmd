cmd_sound/soc/codecs/snd-soc-rl6231.mod := printf '%s\n'   rl6231.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-rl6231.mod
