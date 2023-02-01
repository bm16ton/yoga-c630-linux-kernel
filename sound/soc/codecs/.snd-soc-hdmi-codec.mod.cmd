cmd_sound/soc/codecs/snd-soc-hdmi-codec.mod := printf '%s\n'   hdmi-codec.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-hdmi-codec.mod
