cmd_sound/soc/codecs/snd-soc-tlv320aic23-i2c.mod := printf '%s\n'   tlv320aic23-i2c.o | awk '!x[$$0]++ { print("sound/soc/codecs/"$$0) }' > sound/soc/codecs/snd-soc-tlv320aic23-i2c.mod
