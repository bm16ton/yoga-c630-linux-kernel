cmd_sound/soc/codecs/snd-soc-cs42l83-i2c.mod := printf '%s\n'   cs42l83-i2c.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-cs42l83-i2c.mod
