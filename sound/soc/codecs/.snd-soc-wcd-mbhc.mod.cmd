cmd_sound/soc/codecs/snd-soc-wcd-mbhc.mod := printf '%s\n'   wcd-mbhc-v2.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-wcd-mbhc.mod
