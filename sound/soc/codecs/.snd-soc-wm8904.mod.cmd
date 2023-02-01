cmd_sound/soc/codecs/snd-soc-wm8904.mod := printf '%s\n'   wm8904.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-wm8904.mod
