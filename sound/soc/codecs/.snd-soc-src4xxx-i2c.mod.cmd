cmd_sound/soc/codecs/snd-soc-src4xxx-i2c.mod := printf '%s\n'   src4xxx-i2c.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-src4xxx-i2c.mod
