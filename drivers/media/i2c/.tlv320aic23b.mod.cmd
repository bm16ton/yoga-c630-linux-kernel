cmd_drivers/media/i2c/tlv320aic23b.mod := printf '%s\n'   tlv320aic23b.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tlv320aic23b.mod
